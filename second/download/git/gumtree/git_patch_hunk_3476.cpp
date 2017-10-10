 	va_start(params, err);
 	error_routine(err, params);
 	va_end(params);
 	return -1;
 }
 
+void warning_errno(const char *warn, ...)
+{
+	char buf[1024];
+	va_list params;
+
+	va_start(params, warn);
+	warn_routine(fmt_with_err(buf, sizeof(buf), warn), params);
+	va_end(params);
+}
+
 void warning(const char *warn, ...)
 {
 	va_list params;
 
 	va_start(params, warn);
 	warn_routine(warn, params);
