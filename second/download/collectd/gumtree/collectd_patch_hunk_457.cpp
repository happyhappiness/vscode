 #include "plugin.h"
 
 /* vcomplain returns 0 if it did not report, 1 else */
 static int vcomplain (int level, c_complain_t *c,
 		const char *format, va_list ap)
 {
-	cdtime_t now;
+	time_t now;
 	char   message[512];
 
-	now = cdtime ();
+	now = time (NULL);
 
 	if (c->last + c->interval > now)
 		return 0;
 
 	c->last = now;
 
-	if (c->interval < interval_g)
-		c->interval = interval_g;
+	if (c->interval < plugin_get_interval ())
+		c->interval = plugin_get_interval ();
 	else
 		c->interval *= 2;
 
-	if (c->interval > TIME_T_TO_CDTIME_T (86400))
-		c->interval = TIME_T_TO_CDTIME_T (86400);
+	if (c->interval > 86400)
+		c->interval = 86400;
 
 	vsnprintf (message, sizeof (message), format, ap);
 	message[sizeof (message) - 1] = '\0';
 
 	plugin_log (level, "%s", message);
 	return 1;
 } /* vcomplain */
 
 void c_complain (int level, c_complain_t *c, const char *format, ...)
 {
 	va_list ap;
 
+	/* reset the old interval */
+	if (c->interval < 0)
+		c->interval *= -1;
+
 	va_start (ap, format);
-	if (vcomplain (level, c, format, ap))
-		c->complained_once = 1;
+	vcomplain (level, c, format, ap);
 	va_end (ap);
 } /* c_complain */
 
 void c_complain_once (int level, c_complain_t *c, const char *format, ...)
 {
 	va_list ap;
 
-	if (c->complained_once)
+	if (c->interval < 0)
 		return;
 
 	va_start (ap, format);
 	if (vcomplain (level, c, format, ap))
-		c->complained_once = 1;
+		c->interval *= -1;
 	va_end (ap);
 } /* c_complain_once */
 
 void c_do_release (int level, c_complain_t *c, const char *format, ...)
 {
 	char message[512];
 	va_list ap;
 
 	if (c->interval == 0)
 		return;
 
 	c->interval = 0;
-	c->complained_once = 0;
 
 	va_start (ap, format);
 	vsnprintf (message, sizeof (message), format, ap);
 	message[sizeof (message) - 1] = '\0';
 	va_end (ap);
 
