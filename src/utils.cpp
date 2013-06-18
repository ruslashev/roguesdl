#include "utils.hpp"

void fatal(int code, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	fprintf(stderr, "%sERROR%s ", "\e[31m", "\e[0m");
	vfprintf(stderr, format, args);
	va_end(args);

	exit(code);
}

void warning(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printf("%sWARNING%s ", "\e[33m", "\e[0m");
	vprintf(format, args);
	va_end(args);
}
