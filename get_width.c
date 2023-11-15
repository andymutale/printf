#include "main.h"

int get_width(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int width = 0;

	while (format[curr_i] != '\0')
	{
		if (is_digit(format[curr_i]))
		{
			width = width * 10 + format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			width = va_arg(list, int);
			break;
		}
		else
			break;

		curr_i++;
	}

	*i = curr_i - 1;

	return (width);
}

