#define error(...) (error(__VA_ARGS__), const_error())
#define error_errno(...) (error_errno(__VA_ARGS__), const_error())
#endif

extern void set_die_routine(NORETURN_PTR void (*routine)(const char *err, va_list params));
extern void set_error_routine(void (*routine)(const char *err, va_list params));
extern void set_die_is_recursing_routine(int (*routine)(void));
extern void set_error_handle(FILE *);

extern int starts_with(const char *str, const char *prefix);

/*
