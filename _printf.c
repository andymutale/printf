#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// ... (Your helper functions here) ...

void print_number(char *buffer, int *index, int n, int base, int uppercase) {
    if (n / base) {
        print_number(buffer, index, n / base, base, uppercase);
    }
    char c = n % base < 10 ? '0' + n % base : (uppercase ? 'A' : 'a') + n % base - 10;
    add_to_buffer(buffer, index, c);
}

int _printf(const char *format, ...) {
    va_list args;
    int count = 0;
    char buffer[BUFFER_SIZE];
    int buffer_index = 0;

    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] != '%') {
            add_to_buffer(buffer, &buffer_index, format[i]);
            count++;
        } else {
            i++;
            // Handle flags...
            // Handle length modifiers...
            // Handle field width...
            // Handle precision...
            switch (format[i]) {
                case 'd':
                case 'i': {
                    int n = va_arg(args, int); // For normal
                    // Calculate the number of digits in n...
                    int digits = /* ... */;
                    char fill = flag_zero && precision == -1 ? '0' : ' ';
                    if (!flag_minus) {
                        for (int j = digits; j < width; j++) {
                            add_to_buffer(buffer, &buffer_index, fill);
                            count++;
                        }
                    }
                    if (n < 0) {
                        add_to_buffer(buffer, &buffer_index, '-');
                        n = -n;
                    } else if (flag_plus) {
                        add_to_buffer(buffer, &buffer_index, '+');
                    } else if (flag_space) {
                        add_to_buffer(buffer, &buffer_index, ' ');
                    }
                    print_number(buffer, &buffer_index, n, 10, 0);
                    if (flag_minus) {
                        for (int j = digits; j < width; j++) {
                            add_to_buffer(buffer, &buffer_index, fill);
                            count++;
                        }
                    }
                    break;
                }
                // Handle other specifiers...
                default:
                    break;
            }
        }
    }

    flush_buffer(buffer, &buffer_index);

    va_end(args);

    return count;
}
