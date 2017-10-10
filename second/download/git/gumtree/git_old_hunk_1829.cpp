#define va_copy(dst, src) __va_copy(dst, src)
#else
#define va_copy(dst, src) ((dst) = (src))
#endif
#endif

#if defined(__GNUC__) || (_MSC_VER >= 1400)
#define HAVE_VARIADIC_MACROS 1
#endif

/*
 * Preserves errno, prints a message, but gives no warning for ENOENT.
 * Always returns the return value of unlink(2).
 */
int unlink_or_warn(const char *path);
/*
 * Likewise for rmdir(2).
 */
int rmdir_or_warn(const char *path);
/*
 * Calls the correct function out of {unlink,rmdir}_or_warn based on
 * the supplied file mode.
 */
