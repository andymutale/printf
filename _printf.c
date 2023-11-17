#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int _printf(const char *format, ...)
{
 va_list args;
 va_start(args, format);

 char buffer[-1];
 int buffer_index = 0;

 for (int i = 0; format[i] != '\0'; i++)
 {
 if (format[i] == '%')
 {
  i++;
  switch (format[i])
  {
      case 'R':
      {
        char *str = va_arg(args, char *);
        while (*str)
        {
          if ((*str >= 'a' && *str <= 'm') || (*str >= 'A' && *str <= 'M'))
          {
            buffer[buffer_index++] = *str + 13;
          }
          else if ((*str >= 'n' && *str <= 'z') || (*str >= 'N' && *str <= 'Z'))
          {
            buffer[buffer_index++] = *str - 13;
          }
          else
          {
            buffer[buffer_index++] = *str;
          }
          if (buffer_index == 1024)
          {
            write(1, buffer, buffer_index);
            buffer_index = 0;
          }
          str++;
        }
        break;
      }
      // ... other cases ...
      default:
        break;
  }
 }
 else
 {
  buffer[buffer_index++] = format[i];
 }

 if (buffer_index == 1024)
 {
  write(1, buffer, buffer_index);
  buffer_index = 0;
 }
 }

 if (buffer_index > 0)
 {
 write(1, buffer, buffer_index);
 }

 va_end(args);
 return buffer_index;
}
