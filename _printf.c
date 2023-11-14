#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom printf function with limited functionality
 * @format: Format string containing conversion specifiers
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	if (format == NULL)
		return (-1);

	va_list args;
	int count = 0;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case 'c':
				count += _putchar(va_arg(args, int));
				break;
			case 's':
				count += _puts(va_arg(args, char *));
				break;
			case '%':
				count += _putchar('%');
				break;
			default:
				count += _putchar('%');
				count += _putchar(*format);
			}
		}
		else
		{
			count += _putchar(*format);
		}

		format++;
	}

	va_end(args);

	return (count);
}

/**
 * _putchar - Writes a character to stdout
 * @c: Character to write
 * Return: 1 on success, -1 on error
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - Writes a string to stdout
 * @str: String to write
 * Return: Number of characters written
 */
int _puts(char *str)
{
	if (str == NULL)
		str = "(null)";

	int count = 0;

	while (*str != '\0')
	{
		count += _putchar(*str);
		str++;
	}

	return (count);
}

