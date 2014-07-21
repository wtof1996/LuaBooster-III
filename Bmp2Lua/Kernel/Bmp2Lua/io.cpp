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
#include <boost/filesystem/operations.hpp>
#include "io.hpp"

io::MyByte io::RGB888_to_RGB555(const unsigned char r, const unsigned char g, const unsigned char b)
{

    string byte_seq("1");//The Highest bit must be 1
    bitset<8> t_r(r);
    bitset<8> t_g(g);
    bitset<8> t_b(b);

    byte_seq += t_r.to_string().substr(0, 5);
    byte_seq += t_g.to_string().substr(0, 5);
    byte_seq += t_b.to_string().substr(0, 5);

    //a byte has 8 bits
    //split a RGB555 pixel into 2 bytes
    bitset<8> low(byte_seq, 0, 8);
    bitset<8> high(byte_seq, 8, 8);

    return std::make_pair(static_cast<unsigned char>(low.to_ulong()),
                         static_cast<unsigned char>(high.to_ulong())
                         );
}

void io::Image::convert()
{

}
