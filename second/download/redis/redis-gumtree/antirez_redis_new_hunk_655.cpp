int	malloc_vsnprintf(char *str, size_t size, const char *format,
    va_list ap);
int	malloc_snprintf(char *str, size_t size, const char *format, ...)
    JEMALLOC_FORMAT_PRINTF(3, 4);
void	malloc_vcprintf(void (*write_cb)(void *, const char *), void *cbopaque,
    const char *format, va_list ap);
void malloc_cprintf(void (*write)(void *, const char *), void *cbopaque,
    const char *format, ...) JEMALLOC_FORMAT_PRINTF(3, 4);
void	malloc_printf(const char *format, ...) JEMALLOC_FORMAT_PRINTF(1, 2);

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#ifndef JEMALLOC_ENABLE_INLINE
int	jemalloc_ffsl(long bitmap);
int	jemalloc_ffs(int bitmap);
size_t	pow2_ceil(size_t x);
size_t	lg_floor(size_t x);
void	set_errno(int errnum);
int	get_errno(void);
#endif

#if (defined(JEMALLOC_ENABLE_INLINE) || defined(JEMALLOC_UTIL_C_))

/* Sanity check. */
#if !defined(JEMALLOC_INTERNAL_FFSL) || !defined(JEMALLOC_INTERNAL_FFS)
#  error Both JEMALLOC_INTERNAL_FFSL && JEMALLOC_INTERNAL_FFS should have been defined by configure
#endif

JEMALLOC_ALWAYS_INLINE int
jemalloc_ffsl(long bitmap)
{

	return (JEMALLOC_INTERNAL_FFSL(bitmap));
}

JEMALLOC_ALWAYS_INLINE int
jemalloc_ffs(int bitmap)
{

	return (JEMALLOC_INTERNAL_FFS(bitmap));
}

/* Compute the smallest power of 2 that is >= x. */
JEMALLOC_INLINE size_t
pow2_ceil(size_t x)
