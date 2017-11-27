 
 	return (0);
 } /* int plugin_dispatch_notification */
 
 void plugin_log (int level, const char *format, ...)
 {
-	char msg[512];
+	char msg[1024];
 	va_list ap;
 
 	void (*callback) (int, const char *);
 	llentry_t *le;
 
 	if (list_log == NULL)
