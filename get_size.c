#include "main.h"

int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	switch (format[curr_i]) {
		case 'l':
			size = S_LONG;
			break;
		case 'h':
			size = S_SHORT;
			break;
		default:
			curr_i--;
			break;
	}

	*i = curr_i;

	return (size);
}

