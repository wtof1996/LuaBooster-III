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

#include "draw.hpp"
#include "io.hpp"

auto _VERSION = "V3.01 Alpha I Build 10141656";

namespace option = boost::program_options;
using MyString = std::string;
namespace file = boost::filesystem;

file::path Settings::getInPath() {return inPath;}

file::path Settings::getOutPath() {return outPath;}

file::path Settings::getSavePath() {return savePath;}

file::path Settings::getLunaPath() { return lunaPath;}

file::path Settings::getSearchPath() { return searchPath;}

bool Settings::isOverWrite() { return overWrite;}
bool Settings::isOnlyPreprocess() { return onlyPreprocess;}
bool Settings::isOnlyCompile() { return onlyCompile;}
bool Settings::isDeComment() { return deComment;}
bool Settings::isSaveResult() { return saveResult;}
bool Settings::isSearchOthers() { return searchOthers;}

void Settings::setValue(const option::variables_map &v)
{
    return;
}

namespace draw
{
    void lic_info()
    {
        io::notice(

        "iLua Kernel V3\n"
        "\n"
        "Copyright 2014 wtof1996\n"
        "Licensed under the Apache License, Version 2.0 (the \"License\");\n"
        "you may not use this file except in compliance with the License.\n"
        "You may obtain a copy of the License at\n"

        "    http://www.apache.org/licenses/LICENSE-2.0\n"

        "Unless required by applicable law or agreed to in writing, software\n"
        "distributed under the License is distributed on an \"AS IS\" BASIS,\n"
        "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
        "See the License for the specific language governing permissions and\n"
        "limitations under the License.\n"

        "this software is based in part on the Boost library.\n"
        );

    }//lic_info

    void processOptions(int argc, char *argv[])
    {
        option::options_description desc("Usage");

        desc.add_options()
            ("help,h", "show this help message")
            ("license,l", "show the license")
            ("input,i", option::value<MyString>(), "the path of the input lua or make file, only accept UTF8 file")
            ("output,o", option::value<MyString>(), "the path of the result TNS file or lua file, depend on the options")
            ("save,s", option::value<MyString>(), "save the result of preprocessed lua file, force overwrite if the target has already existed")
            ("includeDirectory,ID", option::value<MyString>(), "indicate the default search directory")
            ("luna", option::value<MyString>(), "indicate the path of Luna")
            ("preprocess,p", "only preprocess, this option will generate a lua file")
            ("compile,c", "directly compile the lua file without preprocess")
            ("decomment,d", "delete all comments , useless blank lines and blanks")
            ("overwrite,w", "overwrite the output file if it exists")
        ;

        option::variables_map vm;

        try{
            option::store(option::parse_command_line(argc, argv, desc), vm);
            option::notify(vm);
        }
        catch(option::error_with_option_name e){
            io::log(e.what());
            exit(EXIT_FAILURE);
        }
        catch(option::error e){
            io::log(e.what());
            exit(EXIT_FAILURE);
        }

        if(vm.count("help")) {
            io::notice(desc);
            exit(EXIT_SUCCESS);
        }
        else if(vm.count("license")) {
            lic_info();
            exit(EXIT_SUCCESS);
        }
        else if(vm.count("input") && vm.count("output")){
            Settings::get().setValue(vm);
        }
        else {
            io::log("no input path or output path, terminated");
            io::log("use --help option for help message");
            exit(EXIT_FAILURE);
        }
    }

    void checkPath()
    {

    }

    void showWelcomeInfo()
    {
        io::notice("============================================");
        io::notice("iLua Kernel");
        io::notice(_VERSION);
        io::notice("Copyright 2014 wtof1996");
        io::notice("Use '-l' or '--license' to show the license");
        io::notice("============================================");
    }
}
