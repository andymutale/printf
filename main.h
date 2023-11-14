#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

/* Flags for formatting options */
#define LEFT_JUSTIFY 1
#define SHOW_SIGN 2
#define SPACE_SIGN 4
#define PREFIX 8
#define ZERO_PAD 16

void print_buffer(char buffer[], int *buff_ind);

int _printf(const char *format, ...);
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
int handle_print(const char *format, int *i, va_list list, char buffer[],
                 int flags, int width, int precision, int size);

#endif /* MAIN_H */

