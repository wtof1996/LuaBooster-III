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

#include <cstdlib>

#include <boost/progress.hpp>

#include "draw.hpp"
#include "io.hpp"

auto _VERSION = "V3.02 Alpha I Build 01251848";

int main(int argc, char *argv[])
{


    draw::process_options(argc, argv);

    io::notice("============================================");
    io::notice("Bmp2Lua Kernel");
    io::notice(_VERSION);
    io::notice("Copyright 2014 wtof1996");
    io::notice("Use '-l' or '--license' to show the license");
    io::notice("============================================");


    draw::check_path();

    io::Image img;
    boost::progress_timer t;

    img.readImage();
    img.convert();

    io::output(img);

    io::notice("Elapsed time:", false);
    //When progress_timer destruct it will show the time elapsed.

    return EXIT_SUCCESS;
}
