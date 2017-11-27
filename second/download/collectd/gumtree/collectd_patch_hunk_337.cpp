 void plugin_log (int level, const char *format, ...)
 {
 	char msg[1024];
 	va_list ap;
 	llentry_t *le;
 
+	if (list_log == NULL)
+	{
+		va_start (ap, format);
+		vfprintf (stderr, format, ap);
+		va_end (ap);
+		return;
+	}
+
 #if !COLLECT_DEBUG
 	if (level >= LOG_DEBUG)
 		return;
 #endif
 
 	va_start (ap, format);
 	vsnprintf (msg, sizeof (msg), format, ap);
 	msg[sizeof (msg) - 1] = '\0';
 	va_end (ap);
 
-	if (list_log == NULL)
-	{
-		fprintf (stderr, "%s\n", msg);
-		return;
-	}
-
 	le = llist_head (list_log);
 	while (le != NULL)
 	{
 		callback_func_t *cf;
 		plugin_log_cb callback;
 
