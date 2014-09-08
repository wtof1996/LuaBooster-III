/*    Lua2Bmp Kernel V3
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

#include "io.hpp"
#include "draw.hpp"

#include <boost/format.hpp>
#include <sstream>
#include <bitset>

#include <cctype>

using std::vector;
using std::string;
using std::bitset;
using std::make_pair;
using boost::iequals;
using namespace boost::gil;
namespace file = boost::filesystem;

unsigned int readByte(file::ifstream &fin)
{
    char read;
    unsigned char ret = 0;

    fin.get(read);
    if(read == '\\'){
        for(int i = 0; i < 3; ++i){
            fin.get(read);
            if(isdigit(read) == 0){
                fin.unget();
                break;
            }
            ret = ret * 10 + (read - '0');
        }
    }
    else if(read == '\"'){
        while(fin.get(read), read == '\"');
        fin.unget();
        return io::NIL;
    }
    else if(read == 0x0d || read == 0x0a) return io::NIL;
    else ret = read;
    return ret;
}

unsigned char io::getByte(file::ifstream &fin)
{
    unsigned int ret;
    do
        ret = readByte(fin);
    while(ret == io::NIL);

    return static_cast<unsigned char>(ret);
}

rgb8_pixel_t io::RGB555_to_RGB888(const io::MyByte &p)
{
    bitset<8> low(p.first);
    bitset<8> high(p.second);

    string byte_seq(low.to_string() + high.to_string());

    bitset<5> r(byte_seq.substr(1, 5));
    bitset<5> g(byte_seq.substr(6, 5));
    bitset<5> b(byte_seq.substr(11, 5));

    return rgb8_pixel_t(r.to_ulong() << 3, g.to_ulong() << 3, b.to_ulong() << 3);
}
void io::output(Image &img)
{
    string ext = file::extension(Settings::get().getOutPath());

    io::notice("Writing to:  " + Settings::get().getOutPath().string());

    if(iequals(ext, ".jpeg") || iequals(ext, ".jpg")){
        try{
            jpeg_write_view(Settings::get().getOutPath().string(), img.getView());
        }
        catch(std::ios_base::failure e){
            io::log("Invalid JPEG file,please check the filename and try again.");
            exit(EXIT_FAILURE);
        }

    }
    else if(iequals(ext, ".png")){
        try{
            png_write_view(Settings::get().getOutPath().string(), img.getView());
        }
        catch(std::ios_base::failure e){
            io::log("Invalid PNG file,please check the filename and try again.");
            exit(EXIT_FAILURE);
        }
    }
    else{
        io::log("Unknown error, terminated.");
        exit(EXIT_FAILURE);
    }

    io::notice("Complete.");
}

void io::Image::readLuaImage()
{
    auto get_char_bits = [](char &&s){return bitset<8>(s).to_string();};
    auto get_ulong = [](string &&s){return bitset<32>(s).to_ulong();};

    file::ifstream fin(Settings::get().getInPath());

    if(!fin){
        io::log("Cannot open input file.");
        exit(EXIT_FAILURE);
    }

    ///READHEADER

    io::notice("Reading header......", false);

    for(size_t i = 0; i < 20; ++i){
        header[i] = getByte(fin);

    }

    std::stringstream s;
    for(int i = 3; i >= 0; --i) s << get_char_bits(header[i]);
    size.first = get_ulong(s.str());
    s.str("");

    for(size_t i = 7; i >= 4; --i) s << get_char_bits(header[i]);
    size.second = get_ulong(s.str());

    io::notice("Complete.");
    io::notice("Image Width:", false);
    io::notice(size.first);
    io::notice("Image Height:", false);
    io::notice(size.second);

    ///READDATA

    io::notice("Reading header......", false);

    auto w = size.first, h = size.second;
    for(decltype(h) y = 0; y < h; ++y){
        for(decltype(w) x = 0; x < w; ++x){
            auto l = getByte(fin), h = getByte(fin);
            data.push_back(make_pair(h, l));
        }
    }

    io::notice("Complete.");

}

void io::Image::convert()
{
    rgb8_image_t tmp_img(size.first, size.second);
    rgb8_view_t tmp_view = view(tmp_img);
    auto w = size.first, h = size.second;
    auto i = data.begin();

    io::notice("Converting.........", false);

    for(decltype(h) y = 0; y < h; ++y){
        for(decltype(w) x = 0; x < w; ++x){
            tmp_view(x, y) = io::RGB555_to_RGB888(*i++);
        }
    }

    src = tmp_img;
    src_view = view(src);

    io::notice("Complete.");
}
