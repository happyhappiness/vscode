#define error(...) (error(__VA_ARGS__), const_error())
#endif

extern void set_die_routine(NORETURN_PTR void (*routine)(const char *err, va_list params));
extern void set_error_routine(void (*routine)(const char *err, va_list params));
extern void set_die_is_recursing_routine(int (*routine)(void));

extern int starts_with(const char *str, const char *prefix);

/*
 * If the string "str" begins with the string found in "prefix", return 1.
 * The "out" parameter is set to "str + strlen(prefix)" (i.e., to the point in
