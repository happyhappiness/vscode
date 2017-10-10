 	while (!strbuf_getline_lf(&sb, in)) {
 		const char *str;
 
 		if (skip_prefix(sb.buf, "# User ", &str))
 			fprintf(out, "From: %s\n", str);
 		else if (skip_prefix(sb.buf, "# Date ", &str)) {
-			unsigned long timestamp;
+			timestamp_t timestamp;
 			long tz, tz2;
 			char *end;
 
 			errno = 0;
-			timestamp = strtoul(str, &end, 10);
+			timestamp = parse_timestamp(str, &end, 10);
 			if (errno)
 				return error(_("invalid timestamp"));
 
 			if (!skip_prefix(end, " ", &str))
 				return error(_("invalid Date line"));
 
