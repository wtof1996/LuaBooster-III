#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <cstdlib>
#include <string>
namespace option = boost::program_options;

void lic_info();
void process_options(int argc, char *argv[]);


#endif // DRAW_HPP_INCLUDED
