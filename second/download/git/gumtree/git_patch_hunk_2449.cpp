  *
  * Copyright (C) Linus Torvalds, 2005
  */
 #include "git-compat-util.h"
 #include "cache.h"
 
-void vreportf(const char *prefix, const char *err, va_list params)
-{
-	char msg[4096];
-	vsnprintf(msg, sizeof(msg), err, params);
-	fprintf(stderr, "%s%s\n", prefix, msg);
-}
+static FILE *error_handle;
+static int tweaked_error_buffering;
 
-void vwritef(int fd, const char *prefix, const char *err, va_list params)
+void vreportf(const char *prefix, const char *err, va_list params)
 {
-	char msg[4096];
-	int len = vsnprintf(msg, sizeof(msg), err, params);
-	if (len > sizeof(msg))
-		len = sizeof(msg);
+	FILE *fh = error_handle ? error_handle : stderr;
 
-	write_in_full(fd, prefix, strlen(prefix));
-	write_in_full(fd, msg, len);
-	write_in_full(fd, "\n", 1);
+	fflush(fh);
+	if (!tweaked_error_buffering) {
+		setvbuf(fh, NULL, _IOLBF, 0);
+		tweaked_error_buffering = 1;
+	}
+
+	fputs(prefix, fh);
+	vfprintf(fh, err, params);
+	fputc('\n', fh);
 }
 
 static NORETURN void usage_builtin(const char *err, va_list params)
 {
 	vreportf("usage: ", err, params);
 	exit(129);
