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
#include <cstdlib>
#include <string>
#include <sstream>

#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>

#include "io.hpp"
#include "draw.hpp"

//#define ____DEBUG

namespace option = boost::program_options;
using MyString = std::string;
namespace file = boost::filesystem;


void Settings::setValue(const option::variables_map &v)
{
    inPath = v["input"].as<MyString>();
    outPath = v["output"].as<MyString>();
    rawOutput = v.count("raw");
    overWrite = v.count("overwrite");
    if(v.count("resize")){
        std::stringstream tmp;
        tmp.str(v["resize"].as<MyString>());
        char t;
        tmp >> size.first >> t >> size.second;
#ifdef ____DEBUG
        //io::notice(v["resize"].as<MyString>());
#endif // ____DEBUG
        if(t != '*'){
            io::log("unrecongnised size value.");
            std::exit(EXIT_FAILURE);
        }
        this->resize = true;
    }
}

namespace draw{
    using namespace std;
    void lic_info()
    {
        io::notice(

        "Bmp2Lua Kernel V3\n"
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

        "this software is based in part on the work of the Independent JPEG Group.\n"
        "this software is based in part on the libpng library.\n"
        "this software is based in part on the Boost library.\n"
        );

    }//lic_info

    void process_options(int argc, char *argv[])
    {
        option::options_description desc("Usage");

        desc.add_options()
            ("help,h", "show this help message")
            ("license,l", "show the license")
            ("input,i", option::value<MyString>(), "the path of the input image file, only accept png or jpeg file")
            ("output,o", option::value<MyString>(), "the path of the result file")
            ("resize,r", option::value<MyString>(), "using bilinear resampling to scale the image.the size must be given by 'widthg*height', e.g 320*240")
            ("raw", "use the raw output instead of the TI offcial output")
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
#ifdef ____DEBUG
        using namespace io;
       /* notice(Settings::get().getInPath());
        notice(Settings::get().getOutPath());
        notice(Settings::get().isRaw());
        notice(Settings::get().isOverWrite());

        notice(Settings::get().getSize().first);
        notice(Settings::get().getSize().second);*/
       // notice(file::exists(Settings::get().getOutPath().branch_path()));


#endif // ____DEBUG
        }
        else {
            io::log("no input path or output path, terminated");
            io::log("use --help option for help message");
            exit(EXIT_FAILURE);
        }
    }//process_options

    void check_path()
    {
        Settings &s = Settings::get();
        if(! (file::exists(s.getInPath()) &&
              file::is_regular_file(s.getInPath()))
          ) {
                io::log("Invalid input file, please check the path and try again.");
                exit(EXIT_FAILURE);
        }
        if(!file::exists(s.getOutPath().branch_path())){
                io::log("Invalid output file path, please check the path and try again.");
                exit(EXIT_FAILURE);
        }

        if(file::exists(s.getOutPath()) && !s.isOverWrite()){
                io::log("The output file has already existed, use the 'overwrite' option.");
                exit(EXIT_FAILURE);
        }
    }

};//draw

