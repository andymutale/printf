#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

int _printf(const char *format, ...);
void print_to_buffer(char *buffer, int *index, char c);
void print_integer(char *buffer, int *index, int value, int plus_sign, int space);
void print_rot13(char *buffer, int *index, char *str);
void print_reversed(char *buffer, int *index, char *str);

#endif /* MAIN_H */

