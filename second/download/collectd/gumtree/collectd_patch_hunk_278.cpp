 	if (c->interval > 86400)
 		c->interval = 86400;
 
 	vsnprintf (message, sizeof (message), format, ap);
 	message[sizeof (message) - 1] = '\0';
 
-	plugin_log (level, message);
+	plugin_log (level, "%s", message);
 	return 1;
 } /* vcomplain */
 
 void c_complain (int level, c_complain_t *c, const char *format, ...)
 {
 	va_list ap;
