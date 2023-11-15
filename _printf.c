#include "main.h"

void print_buff(char buff[], int *buff_index);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int i, printed_chars = 0, buff_index = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_index++] = format[i];
            if (buff_index == BUFF_SIZE)
                print_buff(buffer, &buff_index);
            printed_chars++;
        }
        else
        {
            print_buff(buffer, &buff_index);
            i++;
            printed_chars += handle_print(format, &i, list, buffer);
            if (printed_chars == -1)
                return (-1);
        }
    }

    print_buff(buffer, &buff_index);

    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buff(char buffer[], int *buff_index)
{
    if (*buff_index > 0)
        write(1, &buffer[0], *buff_index);

    *buff_index = 0;
}

