#define UNUSED(x) (void)(x)

/**
 * handle_write_char - Prints a character
 * @c: Character to be printed
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 *
 * Return: Number of characters printed
 */
int handle_write_char(char c, char buffer[], int flags, int width)
{
	int i = 0;
	char padd = ' ';

	UNUSED(flags);

	if (width > 1)
		return handle_padding(0, buffer, width, 1, padd, 0);

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
		return handle_padding(flags, buffer, width, 1, padd, 0);

	return write(1, &buffer[0], 1);
}

/**
 * write_number - Prints a number
 * @is_negative: Indicator for negative number
 * @ind: Index in the buffer
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(flags);

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

/**
 * handle_padding - Adds padding to the formatted string
 * @flags: Calculates active flags
 * @buffer: Buffer array to handle print
 * @width: Width specifier
 * @length: Length of the buffer
 * @padd: Padding character
 * @extra_c: Extra character
 *
 * Return: Number of characters printed
 */
int handle_padding(int flags, char buffer[], int width, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';

		if (flags & F_MINUS && padd == ' ')
		{
			padd_start = handle_extra_char(buffer, --padd_start, extra_c);
			return padd_start + write(1, &buffer[1], i - 1);
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			i = write(1, &buffer[1], i - 1);
			return i + handle_extra_char(buffer, padd_start, extra_c);
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			padd_start = handle_extra_char(buffer, --padd_start, extra_c);
			return padd_start + write(1, &buffer[padd_start + 1], i - padd_start - 1);
		}
	}

	return handle_extra_char(buffer, padd_start, extra_c);
}

/**
 * handle_precision - Ensures the correct precision for numbers
 * @prec: Precision specifier
 * @length: Length of the buffer
 * @buffer: Buffer array to handle print
 * @ind: Index in the buffer
 *
 * Return: Updated index
 */
int handle_precision(int prec, int length, char buffer[], int ind)
{
	while (prec > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	return ind;
}

/**
 * handle_extra_char - Adds an extra character to the buffer
 * @buffer: Buffer array to handle print
 * @ind: Index in the buffer
 * @extra_c: Extra character
 *
 * Return: Number of characters printed
 */
int handle_extra_char(char buffer[], int ind, char extra_c)
{
	if (extra_c)
		buffer[--ind] = extra_c;

	return write(1, &buffer[ind], 1);
}

/**
 * write_pointer - Prints a pointer
 * @buffer: Buffer array to handle print
 * @ind: Index in the buffer
 * @length: Length of the buffer
 * @width: Width specifier
 * @flags: Calculates active flags
 * @padd: Padding character
 * @extra_c: Extra character
 * @padd_start: Padding start
 *
 * Return: Number of characters printed
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';

		buffer[--ind] = 'x';
		buffer[--ind] = '0';
		if (extra_c)
			buffer[--ind] = extra_c;

		if (flags & F_MINUS && padd == ' ')
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		else if (!(flags & F_MINUS) && padd == ' ')
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		else if (!(flags & F_MINUS) && padd == '0')
			return (write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[ind], length - (1 - padd_start) - 2));
	}
	else
	{
		buffer[--ind] = 'x';
		buffer[--ind] = '0';
		if (extra_c)
			buffer[--ind] = extra_c;
	}

	return write(1, &buffer[ind], BUFF_SIZE - ind - 1);
}
