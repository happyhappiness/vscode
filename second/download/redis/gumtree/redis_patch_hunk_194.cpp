 #include <stdlib.h>
 #include <stdarg.h>
 #include <string.h>
 
 #include "strbuf.h"
 
-void die(const char *fmt, ...)
+static void die(const char *fmt, ...)
 {
     va_list arg;
 
     va_start(arg, fmt);
     vfprintf(stderr, fmt, arg);
     va_end(arg);
