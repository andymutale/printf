#include "main.h"

/**
 * print_char - Prints a character.
 * @types: A va_list of arguments.
 * @buffer: A buffer to store the output.
 * @flags: Flags for formatting.
 * @width: Minimum width of output.
 * @precision: Precision for formatting.
 * @size: Size modifier (e.g., l, h).
 *
 * Return: Number of characters printed.
 */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string.
 * @types: A va_list of arguments.
 * @buffer: A buffer to store the output.
 * @flags: Flags for formatting.
 * @width: Minimum width of output.
 * @precision: Precision for formatting.
 * @size: Size modifier (e.g., l, h).
 *
 * Return: Number of characters printed.
 */
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	if (str == NULL)
		str = "(null)";

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - Prints a percent sign.
 * @types: A va_list of arguments.
 * @buffer: A buffer to store the output.
 * @flags: Flags for formatting.
 * @width: Minimum width of output.
 * @precision: Precision for formatting.
 * @size: Size modifier (e.g., l, h).
 *
 * Return: Number of characters printed.
 */
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	(void)types;
	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	return (write(1, "%%", 1));
}

/**
 * print_int - Prints an integer.
 * @types: A va_list of arguments.
 * @buffer: A buffer to store the output.
 * @flags: Flags for formatting.
 * @width: Minimum width of output.
 * @precision: Precision for formatting.
 * @size: Size modifier (e.g., l, h).
 *
 * Return: Number of characters printed.
 */
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	/* Null-terminate the buffer */
	buffer[i + 1] = '\0';

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints a binary number.
 * @types: A va_list of arguments.
 * @buffer: A buffer to store the output.
 * @flags: Flags for formatting.
 * @width: Minimum width of output.
 * @precision: Precision for formatting.
 * @size: Size modifier (e.g., l, h).
 *
 * Return: Number of characters printed.
 */
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);
	char binary[32];
	int count = 0;

	for (int i = 0; i < 32; i++)
	{
		binary[i] = (n & (1 << (31 - i))) ? '1' : '0';
	}

	for (int i = 0; i < 32; i++)
	{
		if (binary[i] == '1' || i == 31)
		{
			write(1, &binary[i], 1);
			count++;
		}
	}

	return count;
}

