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
#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <cstdlib>
#include <string>
#include <utility>

namespace option = boost::program_options;
using MyString = std::string;
using MySize = std::pair<unsigned int, unsigned int>;
namespace file = boost::filesystem;

class Settings
{
public:
    static Settings& get(){
        static Settings s;
        return s;
    }
    void setValue(const option::variables_map &v);
    bool isRaw() {return rawOutput;}
    bool isOverWrite() { return overWrite;}
    bool isResize() { return resize;}
    file::path getInPath() {return inPath;}
    file::path getOutPath() {return outPath;}
    MySize getSize() {return size;}


private:
    Settings():inPath(""), outPath(""), rawOutput(false), overWrite(false), resize(false), size(0, 0)  {} ;
    file::path inPath;
    file::path outPath;
    bool rawOutput;
    bool overWrite;
    bool resize;
    MySize size;
};


namespace draw{
    void process_options(int argc, char *argv[]);
    void check_path();
};

#endif // DRAW_HPP_INCLUDED
