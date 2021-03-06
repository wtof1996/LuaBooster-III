/*    iLua Kernel V3
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
 *     this software is based in part on the Boost library.
 */
#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>

#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace option = boost::program_options;
using MyString = std::string;
namespace file = boost::filesystem;

class Settings final
{
public:
    static Settings& get(){
        static Settings s;
        return s;
    }

    void setValue(const option::variables_map &v);

    file::path getInPath();
    file::path getOutPath();
    file::path getLunaPath();
    file::path getSavePath();
    file::path getSearchPath();

    bool isOverWrite();
    bool isOnlyPreprocess();
    bool isOnlyCompile();
    bool isDeComment();
    bool isSaveResult();
    bool isSearchOthers();

private:
    Settings() = default;
    file::path inPath, outPath, lunaPath, savePath, searchPath;
    bool overWrite, onlyPreprocess, onlyCompile, deComment, saveResult, searchOthers;
};

namespace draw
{
    void processOptions(int argc, char *argv[]);
    void checkPath();
    void showWelcomeInfo();
}

#endif // DRAW_HPP_INCLUDED
