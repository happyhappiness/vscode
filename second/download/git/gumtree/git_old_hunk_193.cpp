 * Let callers be aware of the constant return value; this can help
 * gcc with -Wuninitialized analysis. We restrict this trick to gcc, though,
 * because some compilers may not support variadic macros. Since we're only
 * trying to help gcc, anyway, it's OK; other compilers will fall back to
 * using the function as usual.
 */
#if defined(__GNUC__) && ! defined(__clang__)
#define error(...) (error(__VA_ARGS__), -1)
#endif

extern void set_die_routine(NORETURN_PTR void (*routine)(const char *err, va_list params));
extern void set_error_routine(void (*routine)(const char *err, va_list params));
extern void set_die_is_recursing_routine(int (*routine)(void));

extern int starts_with(const char *str, const char *prefix);
extern int ends_with(const char *str, const char *suffix);

static inline const char *skip_prefix(const char *str, const char *prefix)
{
	do {
		if (!*prefix)
			return str;
	} while (*str++ == *prefix++);
	return NULL;
}

#if defined(NO_MMAP) || defined(USE_WIN32_MMAP)

#ifndef PROT_READ
#define PROT_READ 1
