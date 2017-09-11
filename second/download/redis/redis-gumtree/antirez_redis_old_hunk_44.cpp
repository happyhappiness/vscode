 * malloc_vsnprintf() supports a subset of snprintf(3) that avoids floating
 * point math.
 */
size_t	malloc_vsnprintf(char *str, size_t size, const char *format,
    va_list ap);
size_t	malloc_snprintf(char *str, size_t size, const char *format, ...)
    JEMALLOC_FORMAT_PRINTF(3, 4);
void	malloc_vcprintf(void (*write_cb)(void *, const char *), void *cbopaque,
    const char *format, va_list ap);
