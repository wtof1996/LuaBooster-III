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
#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <utility>
#include <array>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

namespace io
{
    using std::cout;
    using std::endl;

    template<typename T>
    void notice(const T &i, bool nl = true) { cout << i ;if(nl) cout << endl;}
    template<typename T>
    void notice(const T &&i, bool nl = true) { cout << i ;if(nl) cout << endl;}

    template<typename T>
    void log(const T &i, bool nl = true) { cout << i ;if(nl) cout << endl;}
    template<typename T>
    void log(const T &&i, bool nl = true) { cout << i ;if(nl) cout << endl;}
}

#endif // IO_HPP_INCLUDED
