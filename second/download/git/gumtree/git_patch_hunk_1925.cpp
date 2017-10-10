 extern int strbuf_check_branch_ref(struct strbuf *sb, const char *name);
 
 extern void strbuf_addstr_urlencode(struct strbuf *, const char *,
 				    int reserved);
 extern void strbuf_humanise_bytes(struct strbuf *buf, off_t bytes);
 
+extern void strbuf_add_absolute_path(struct strbuf *sb, const char *path);
+
 __attribute__((format (printf,1,2)))
 extern int printf_ln(const char *fmt, ...);
 __attribute__((format (printf,2,3)))
 extern int fprintf_ln(FILE *fp, const char *fmt, ...);
 
 char *xstrdup_tolower(const char *);
