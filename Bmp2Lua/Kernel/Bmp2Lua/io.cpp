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
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "draw.hpp"
#include "io.hpp"


namespace file = boost::filesystem;
using namespace boost::gil;
using boost::iequals;

void io::Image::readImage()
{
    string ext = file::extension(Settings::get().getInPath());

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
    rgb8_image_t img(src.width(), src.height());
    copy_and_convert_pixels(view(src), view(img));

    if(Settings::get().isResize()){
        MySize s = Settings::get().getSize();
        rgb8_image_t resize_img(s.first, s.second);
        resize_view(view(img), view(resize_img), bilinear_sampler());

        src_image = resize_img;


    }
    else{
        src_image = img;
    }
    src_view = view(src_image);


}

void io::Image::convert()
{
    auto w = src_view.width(), h = src_view.height();
    for(decltype(h) y = 0; y < h; ++y){
        for(decltype(w) x = 0; x < w; ++x){
            data.push_back(io::RGB888_to_RGB555(src_view(x, y)));
        }
    }
}
