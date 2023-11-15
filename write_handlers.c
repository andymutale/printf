#include "main.h"

int handle_padding(int flags, char buffer[], int width, int length, char padd, char extra_c);
int handle_precision(int prec, int length, char buffer[], int ind);
int handle_extra_char(int flags, char buffer[], int ind, char extra_c);

/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		return handle_padding(flags, buffer, width, 1, padd, 0);
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	ind = handle_precision(precision, length, buffer, ind);
	length = BUFF_SIZE - ind - 1;

	return handle_padding(flags, buffer, width, length, padd, extra_ch);
}

int handle_padding(int flags, char buffer[], int width, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';

		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			return handle_extra_char(flags, buffer, --padd_start, extra_c) +
				write(1, &buffer[1], i - 1);
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			return write(1, &buffer[1], i - 1) +
				handle_extra_char(flags, buffer, padd_start, extra_c);
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			return handle_extra_char(flags, buffer, --padd_start, extra_c) +
				write(1, &buffer[padd_start + 1], i - padd_start - 1);
		}
	}

	return handle_extra_char(flags, buffer, padd_start, extra_c);
}

int handle_precision(int prec, int length, char buffer[], int ind)
{
	while (prec > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	return ind;
}

int handle_extra_char(int flags, char buffer[], int ind, char extra_c)
{
	if (extra_c)
		buffer[--ind] = extra_c;

	return write(1, &buffer[ind], 1);
}

int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, i
