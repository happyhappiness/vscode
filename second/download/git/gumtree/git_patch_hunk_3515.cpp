 			ntohl(hdr->hdr_version));
 
 	nr_objects = ntohl(hdr->hdr_entries);
 	use(sizeof(struct pack_header));
 }
 
-static NORETURN void bad_object(unsigned long offset, const char *format,
+static NORETURN void bad_object(off_t offset, const char *format,
 		       ...) __attribute__((format (printf, 2, 3)));
 
-static NORETURN void bad_object(unsigned long offset, const char *format, ...)
+static NORETURN void bad_object(off_t offset, const char *format, ...)
 {
 	va_list params;
 	char buf[1024];
 
 	va_start(params, format);
 	vsnprintf(buf, sizeof(buf), format, params);
 	va_end(params);
-	die(_("pack has bad object at offset %lu: %s"), offset, buf);
+	die(_("pack has bad object at offset %"PRIuMAX": %s"),
+	    (uintmax_t)offset, buf);
 }
 
 static inline struct thread_local *get_thread_data(void)
 {
 #ifndef NO_PTHREADS
 	if (threads_active)
