 
 /*
  * We used to just use "sscanf()", but that's actually way
  * too permissive for what we want to check. So do an anal
  * object header parse by hand.
  */
-int parse_sha1_header(const char *hdr, unsigned long *sizep)
+static int parse_sha1_header_extended(const char *hdr, struct object_info *oi,
+			       unsigned int flags)
 {
-	char type[10];
-	int i;
+	const char *type_buf = hdr;
 	unsigned long size;
+	int type, type_len = 0;
 
 	/*
-	 * The type can be at most ten bytes (including the
-	 * terminating '\0' that we add), and is followed by
+	 * The type can be of any size but is followed by
 	 * a space.
 	 */
-	i = 0;
 	for (;;) {
 		char c = *hdr++;
 		if (c == ' ')
 			break;
-		type[i++] = c;
-		if (i >= sizeof(type))
-			return -1;
+		type_len++;
 	}
-	type[i] = 0;
+
+	type = type_from_string_gently(type_buf, type_len, 1);
+	if (oi->typename)
+		strbuf_add(oi->typename, type_buf, type_len);
+	/*
+	 * Set type to 0 if its an unknown object and
+	 * we're obtaining the type using '--allow-unkown-type'
+	 * option.
+	 */
+	if ((flags & LOOKUP_UNKNOWN_OBJECT) && (type < 0))
+		type = 0;
+	else if (type < 0)
+		die("invalid object type");
+	if (oi->typep)
+		*oi->typep = type;
 
 	/*
 	 * The length must follow immediately, and be in canonical
 	 * decimal format (ie "010" is not valid).
 	 */
 	size = *hdr++ - '0';
