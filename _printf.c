#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    int count = 0;

    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    {
                        char ch = va_arg(args, int);
                        count += write(1, &ch, 1);
                    }
                    break;
                case 's':
                    {
                        const char* str = va_arg(args, const char*);
                        count += write(1, str, strlen(str));
                    }
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    break;
            }
        } else {
            count += write(1, format, 1);
        }

        format++;
    }

    va_end(args);

    return count;
}