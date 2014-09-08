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

#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <utility>
#include <array>

#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include "draw.hpp"

namespace io
{
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::vector;
    using std::string;
    using std::bitset;
    using namespace boost::gil;
    namespace file = boost::filesystem;

    using MyString = std::string;
    using MySize = std::pair<unsigned int, unsigned int>;
    using MyByte = std::pair<unsigned char, unsigned char>;
    using MyHeader = std::array<unsigned char, 20>;
    const int NIL = 0xfffff;


    template<typename T>
    void notice(const T &i, bool nl = true) { cout << i ;if(nl) cout << endl;}
    template<typename T>
    void notice(const T &&i, bool nl = true) { cout << i ;if(nl) cout << endl;}

    template<typename T>
    void log(const T &i, bool nl = true) { cout << i ;if(nl) cout << endl;}
    template<typename T>
    void log(const T &&i, bool nl = true) { cout << i ;if(nl) cout << endl;}

    rgb8_pixel_t RGB555_to_RGB888(const MyByte &p);
    unsigned char getByte(file::ifstream &fin);

    class Image
    {
    public:
        void readLuaImage();
        void convert();
        rgb8_view_t& getView() {return src_view;}
    private:
        rgb8_image_t src;
        rgb8_view_t src_view;
        vector<MyByte> data;
        MyHeader header;
        MySize size;
    };

    void output(Image &img);


};//io


#endif // IO_HPP_INCLUDED
