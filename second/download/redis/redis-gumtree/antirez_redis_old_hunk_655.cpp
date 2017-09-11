int	malloc_vsnprintf(char *str, size_t size, const char *format,
    va_list ap);
int	malloc_snprintf(char *str, size_t size, const char *format, ...)
    JEMALLOC_ATTR(format(printf, 3, 4));
void	malloc_vcprintf(void (*write_cb)(void *, const char *), void *cbopaque,
    const char *format, va_list ap);
void malloc_cprintf(void (*write)(void *, const char *), void *cbopaque,
    const char *format, ...) JEMALLOC_ATTR(format(printf, 3, 4));
void	malloc_printf(const char *format, ...)
    JEMALLOC_ATTR(format(printf, 1, 2));

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#ifndef JEMALLOC_ENABLE_INLINE
size_t	pow2_ceil(size_t x);
void	set_errno(int errnum);
int	get_errno(void);
#endif

#if (defined(JEMALLOC_ENABLE_INLINE) || defined(JEMALLOC_UTIL_C_))
/* Compute the smallest power of 2 that is >= x. */
JEMALLOC_INLINE size_t
pow2_ceil(size_t x)
