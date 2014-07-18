#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <cstdlib>
#include <string>
namespace option = boost::program_options;
using MyString = std::string;

class GlobalSettings
{
public:
    GlobalSettings() = default;
    void setValue(const option::variables_map &v);
    bool getRaw();
    MyString getInPath();
    MyString getOutPath();
private:
    MyString inPath;
    MyString outPath;
    bool rawOutput;
};

namespace draw{
    void lic_info();
    void process_options(int argc, char *argv[], GlobalSettings& s);
};

#endif // DRAW_HPP_INCLUDED
