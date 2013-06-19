#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <cstdarg>

typedef unsigned int uint;

void fatal(int code, const char* format, ...);
void warning(const char* format, ...);

#endif
