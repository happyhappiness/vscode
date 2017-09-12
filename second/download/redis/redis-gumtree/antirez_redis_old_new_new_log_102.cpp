* malloc_vsnprintf() supports a subset of snprintf(3) that avoids floating
 * point math.
 */
size_t	malloc_vsnprintf(char *str, size_t size, const char *format,
    va_list ap);