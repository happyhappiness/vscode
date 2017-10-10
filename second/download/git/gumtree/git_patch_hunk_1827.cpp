 #endif
 
 #include "compat/bswap.h"
 
 #include "wildmatch.h"
 
+struct strbuf;
+
 /* General helper functions */
 extern void vreportf(const char *prefix, const char *err, va_list params);
 extern void vwritef(int fd, const char *prefix, const char *err, va_list params);
 extern NORETURN void usage(const char *err);
 extern NORETURN void usagef(const char *err, ...) __attribute__((format (printf, 1, 2)));
 extern NORETURN void die(const char *err, ...) __attribute__((format (printf, 1, 2)));
