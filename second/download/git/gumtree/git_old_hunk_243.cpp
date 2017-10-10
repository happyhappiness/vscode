
__attribute__((format (printf,1,2)))
extern int printf_ln(const char *fmt, ...);
__attribute__((format (printf,2,3)))
extern int fprintf_ln(FILE *fp, const char *fmt, ...);

#endif /* STRBUF_H */
