/*    Bmp2Lua Kernel V3
 *
 *    Copyright 2014 wtof1996
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *     this software is based in part on the work of the Independent JPEG Group.
 *     this software is based in part on the libpng library.
 *     this software is based in part on the Boost library.
 */

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <array>
#include <cctype>

#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/progress.hpp>

#include "draw.hpp"
#include "io.hpp"

//#define INFO

namespace file = boost::filesystem;
using namespace boost::gil;
using boost::iequals;
using boost::progress_display;

void io::Image::readImage()
{
    string ext = file::extension(Settings::get().getInPath());

    io::notice("Reading from:  " + Settings::get().getInPath().string());

    if(iequals(ext, ".jpeg") || iequals(ext, ".jpg")){
        try{
            jpeg_read_image(Settings::get().getInPath().string(), src);
        }
        catch(std::ios_base::failure e){
            log("Invalid JPEG file,please check the filename and try again.");
            exit(EXIT_FAILURE);
        }
    }

    else if(iequals(ext, ".png")){
        try{
            png_read_image(Settings::get().getInPath().string(), src);
        }
        catch(std::ios_base::failure e){
            log("Invalid PNG file,please check the filename and try again.");
            exit(EXIT_FAILURE);
        }
    }
    else{
        io::log("Invalid input file, please check the filename and try again.");
        exit(EXIT_FAILURE);
    }

    io::notice("Complete.");
    io::notice("Image Width:", false);
    io::notice(src.width());
    io::notice("Image Height:", false);
    io::notice(src.height());

    rgb8_image_t img(src.width(), src.height());
    copy_and_convert_pixels(view(src), view(img));

    if(Settings::get().isResize()){
        auto s = Settings::get().getSize();

        io::notice("Resize Mode Enabled");
        io::notice("Target Width:", false);
        io::notice(s.first);
        io::notice("Target Height:", false);
        io::notice(s.second);

        rgb8_image_t resize_img(s.first, s.second);
        resize_view(view(img), view(resize_img), bilinear_sampler());

        src_image = resize_img;
        io::notice("Resize complete.");
    }
    else{
        src_image = img;
    }
    src_view = view(src_image);

}

void io::Image::convert()
{
    io::notice("Converting......", false);

    auto get_bits = [](const string &s, unsigned pos, unsigned len){return bitset<8>(s, pos, len);};
    auto get_ulong_bits = [](const unsigned long l){return bitset<32>(l).to_string();};

    //Make Header

    auto w = src_view.width(), h = src_view.height();
    auto i = header.begin();
    auto tmp_str = get_ulong_bits(w);
    //4 bytes for width
    for(int j = 3; j >= 0; --j){
        *i++ = static_cast<unsigned char>(get_bits(tmp_str, j * 8, 8).to_ulong());
    }
    //4 bytes for height
    tmp_str = get_ulong_bits(h);
    for(int j = 3; j >= 0; --j){
        *i++ = static_cast<unsigned char>(get_bits(tmp_str, j * 8, 8).to_ulong());
    }

    // Alignment, Flags, Pad
    for(int j = 3; j >= 0; --j){
        *i++ = 0;
    }

    //Raster
    tmp_str = get_ulong_bits(w * 2);
    for(int j = 3; j >= 0; --j){
        *i++ = static_cast<unsigned char>(get_bits(tmp_str, j * 8, 8).to_ulong());
    }

    *i++ = 16;*i++ = 0;//Bits
    *i++ = 1;*i++ = 0;//Plane
    //Header End

    progress_display status(h * w);

    //Make data
    for(decltype(h) y = 0; y < h; ++y){
        for(decltype(w) x = 0; x < w; ++x){
            data.push_back(io::RGB888_to_RGB555(src_view(x, y)));
            ++status;
        }
    }
    //Data End
}

void io::output(io::Image& img)
{
    //These two functions could produce specific format strings for output
    auto outByte = [](const unsigned char &c){return (boost::format("\\%03d") % static_cast<int>(c)).str();};
    auto outChar = [&outByte](const unsigned char &c){if(!std::isprint(c) || c == '"' || c == '\\') return outByte(c);
                                                      else  return (boost::format("%c") % c).str();
                                                     };

    io::notice("Writing to:  " + Settings::get().getOutPath().string(), false);
    file::ofstream fout(Settings::get().getOutPath(), std::ios::out);
    if(!fout){
        io::log("Cannot open output file");
        std::exit(EXIT_FAILURE);
    }

    fout << "\"";

    auto h =  img.getHeader(); //Header
    auto d = img.getData();    //Data

    for(auto &i: h){
        if(Settings::get().isRaw()) fout << outByte(i);
        else                        fout << outChar(i);
    }

    progress_display status(d.size());
    for(auto &i: d){
        if(Settings::get().isRaw()) fout << outByte(i.first) << outByte(i.second);
        else                        fout << outChar(i.first) << outChar(i.second);
        ++status;
    }

    fout << "\"";

    fout.close();
    fout.clear();

    io::notice("Convert Complete!");

}
