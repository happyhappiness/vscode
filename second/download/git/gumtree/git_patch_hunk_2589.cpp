 	if (parse_date_basic(date, &timestamp, &offset))
 		return -1;
 	date_string(timestamp, offset, result);
 	return 0;
 }
 
-enum date_mode parse_date_format(const char *format)
+void parse_date_format(const char *format, struct date_mode *mode)
 {
 	if (!strcmp(format, "relative"))
-		return DATE_RELATIVE;
+		mode->type = DATE_RELATIVE;
 	else if (!strcmp(format, "iso8601") ||
 		 !strcmp(format, "iso"))
-		return DATE_ISO8601;
+		mode->type = DATE_ISO8601;
 	else if (!strcmp(format, "iso8601-strict") ||
 		 !strcmp(format, "iso-strict"))
-		return DATE_ISO8601_STRICT;
+		mode->type = DATE_ISO8601_STRICT;
 	else if (!strcmp(format, "rfc2822") ||
 		 !strcmp(format, "rfc"))
-		return DATE_RFC2822;
+		mode->type = DATE_RFC2822;
 	else if (!strcmp(format, "short"))
-		return DATE_SHORT;
+		mode->type = DATE_SHORT;
 	else if (!strcmp(format, "local"))
-		return DATE_LOCAL;
+		mode->type = DATE_LOCAL;
 	else if (!strcmp(format, "default"))
-		return DATE_NORMAL;
+		mode->type = DATE_NORMAL;
 	else if (!strcmp(format, "raw"))
-		return DATE_RAW;
-	else
+		mode->type = DATE_RAW;
+	else if (skip_prefix(format, "format:", &format)) {
+		mode->type = DATE_STRFTIME;
+		mode->strftime_fmt = xstrdup(format);
+	} else
 		die("unknown date format %s", format);
 }
 
 void datestamp(struct strbuf *out)
 {
 	time_t now;
