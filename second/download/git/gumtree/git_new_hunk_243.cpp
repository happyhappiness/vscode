
__attribute__((format (printf,1,2)))
extern int printf_ln(const char *fmt, ...);
__attribute__((format (printf,2,3)))
extern int fprintf_ln(FILE *fp, const char *fmt, ...);

char *xstrdup_tolower(const char *);

/*
 * Create a newly allocated string using printf format. You can do this easily
 * with a strbuf, but this provides a shortcut to save a few lines.
 */
__attribute__((format (printf, 1, 0)))
char *xstrvfmt(const char *fmt, va_list ap);
__attribute__((format (printf, 1, 2)))
char *xstrfmt(const char *fmt, ...);

#endif /* STRBUF_H */
