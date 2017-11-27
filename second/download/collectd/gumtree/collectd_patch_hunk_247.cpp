 {
 	free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
 }
 
 #define YYTABLES_NAME "yytables"
 
-#line 59 "scanner.l"
+#line 117 "scanner.l"
+
+
+static void ml_append (char *string)
+{
+	int len = strlen (string);
+	int s;
+
+	if (ml_free <= len) {
+		ml_len += len - ml_free + 1;
+		ml_buffer = (char *)realloc (ml_buffer, ml_len);
+		if (NULL == ml_buffer)
+			YY_FATAL_ERROR ("out of dynamic memory in ml_append");
+	}
 
+	s = snprintf (ml_buffer + ml_pos, ml_free, "%s", string);
+	if ((0 > s) || (ml_free <= s))
+		YY_FATAL_ERROR ("failed to write to multiline buffer");
+
+	ml_pos += s;
+	return;
+} /* ml_append */
 
 
