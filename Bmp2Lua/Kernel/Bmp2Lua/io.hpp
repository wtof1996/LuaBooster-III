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

#pragma once

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

    using MyString = std::string;
    using MySize = std::pair<unsigned int, unsigned int>;
    using MyByte = std::pair<unsigned char, unsigned char>;
    using MyHeader = std::array<unsigned char, 20>;

    typedef boost::mpl::vector<
            rgb8_image_t,
            rgba8_image_t
    > img_types;

    template<typename T>
    void notice(const T &i, bool nl = true) { cout << i ;if(nl) cout << endl;}
    template<typename T>
    void notice(const T &&i, bool nl = true) { cout << i ;if(nl) cout << endl;}

    template<typename T>
    void log(const T &i, bool nl = true) { cout << i ;if(nl) cout << endl;}
    template<typename T>
    void log(const T &&i, bool nl = true) { cout << i ;if(nl) cout << endl;}

    template<typename T>
    MyByte RGB888_to_RGB555(const T &p)
    {

        string byte_seq("1");//The Highest bit must be 1
        bitset<8> r(get_color(p, red_t()));
        bitset<8> g(get_color(p, green_t()));
        bitset<8> b(get_color(p, blue_t()));

        byte_seq += r.to_string().substr(0, 5);
        byte_seq += g.to_string().substr(0, 5);
        byte_seq += b.to_string().substr(0, 5);

        //a byte has 8 bits
        //split a RGB555 pixel into 2 bytes
        bitset<8> low(byte_seq, 8, 8);
        bitset<8> high(byte_seq, 0, 8);

        return std::make_pair(static_cast<unsigned char>(low.to_ulong()),
                              static_cast<unsigned char>(high.to_ulong())
                            );
    }

    class Image
    {
    public:
        void readImage();
        void convert();

        const vector<MyByte>& getData() { return data;}
        MyHeader& getHeader() {return header;}
        Image() = default;
        ~Image() = default;

    private:
        any_image<img_types> src; //Source image
        rgb8_image_t src_image;   //rgb8 Image
        rgb8_view_t src_view;     //rgb8 Image view
        vector<MyByte> data;      //result data
        MyHeader header;          //result file header
    };

    void output(Image& img);

};//io

