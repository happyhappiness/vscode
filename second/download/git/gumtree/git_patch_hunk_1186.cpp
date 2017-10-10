 	va_list params;
 
 	va_start(params, warn);
 	warn_routine(warn, params);
 	va_end(params);
 }
+
+static NORETURN void BUG_vfl(const char *file, int line, const char *fmt, va_list params)
+{
+	char prefix[256];
+
+	/* truncation via snprintf is OK here */
+	if (file)
+		snprintf(prefix, sizeof(prefix), "BUG: %s:%d: ", file, line);
+	else
+		snprintf(prefix, sizeof(prefix), "BUG: ");
+
+	vreportf(prefix, fmt, params);
+	abort();
+}
+
+#ifdef HAVE_VARIADIC_MACROS
+NORETURN void BUG_fl(const char *file, int line, const char *fmt, ...)
+{
+	va_list ap;
+	va_start(ap, fmt);
+	BUG_vfl(file, line, fmt, ap);
+	va_end(ap);
+}
+#else
+NORETURN void BUG(const char *fmt, ...)
+{
+	va_list ap;
+	va_start(ap, fmt);
+	BUG_vfl(NULL, 0, fmt, ap);
+	va_end(ap);
+}
+#endif
