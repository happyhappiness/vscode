 static uintmax_t parse_mark_ref_space(const char **p)
 {
 	uintmax_t mark;
 	char *end;
 
 	mark = parse_mark_ref(*p, &end);
-	if (*end != ' ')
+	if (*end++ != ' ')
 		die("Missing space after mark: %s", command_buf.buf);
 	*p = end;
 	return mark;
 }
 
-static void file_change_m(struct branch *b)
+static void file_change_m(const char *p, struct branch *b)
 {
-	const char *p = command_buf.buf + 2;
 	static struct strbuf uq = STRBUF_INIT;
 	const char *endp;
 	struct object_entry *oe;
 	unsigned char sha1[20];
 	uint16_t mode, inline_data = 0;
 
