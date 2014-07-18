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
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <cstdlib>
#include <string>

#define ____DEBUG

namespace option = boost::program_options;
using MyString = std::string;

class GlobalSettings
{
public:
    void setValue(const option::variables_map &v);
    bool getRaw() {return rawOutput;}
    MyString getInPath() {return inPath;}
    MyString getOutPath() {return outPath;}
private:
    MyString inPath;
    MyString outPath;
    bool rawOutput;
};

void GlobalSettings::setValue(const option::variables_map &v)
{
    inPath = v["input"].as<MyString>();
    outPath = v["output"].as<MyString>();
    rawOutput = !v.count("ti");
}

namespace draw{
    using namespace std;
void lic_info()
{
    cout <<

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
    << endl;

}

void process_options(int argc, char *argv[], GlobalSettings& s)
{
    option::options_description desc("Usage");

    desc.add_options()
        ("help,h", "show this help message")
        ("license,l", "show the license")
        ("input,i", option::value<MyString>(), "the path of the input image file, only accept png or jpeg file")
        ("output,o", option::value<MyString>(), "the path of the result file")
        ("ti,t", "use the TI offcial output instead of the raw output")
    ;
    option::variables_map vm;

    try{
        option::store(option::parse_command_line(argc, argv, desc), vm);
        option::notify(vm);
    }
    catch(option::error_with_option_name e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch(option::error e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    if(vm.count("help")) {
        cout << desc << endl;
        exit(EXIT_SUCCESS);
    }
    else if(vm.count("license")) {
        lic_info();
        exit(EXIT_SUCCESS);
    }
    else if(vm.count("input") && vm.count("output")){
#ifdef ____DEBUG
        cout << "InputPath:" << vm["input"].as<MyString>() << endl;
        cout << "OutputPath:" << vm["output"].as<MyString>() << endl;
#endif
        s.setValue(vm);
    }
    else {
        cout << "no input, terminated" << endl;
        cout << "use --help option for help message" << endl;
    }
}
};

