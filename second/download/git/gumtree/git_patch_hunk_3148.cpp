 	hash_fd(fd, type, vpath, flags, literally);
 }
 
 static void hash_stdin_paths(const char *type, int no_filters, unsigned flags,
 			     int literally)
 {
-	struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;
+	struct strbuf buf = STRBUF_INIT;
+	struct strbuf unquoted = STRBUF_INIT;
 
-	while (strbuf_getline(&buf, stdin, '\n') != EOF) {
+	while (strbuf_getline(&buf, stdin) != EOF) {
 		if (buf.buf[0] == '"') {
-			strbuf_reset(&nbuf);
-			if (unquote_c_style(&nbuf, buf.buf, NULL))
+			strbuf_reset(&unquoted);
+			if (unquote_c_style(&unquoted, buf.buf, NULL))
 				die("line is badly quoted");
-			strbuf_swap(&buf, &nbuf);
+			strbuf_swap(&buf, &unquoted);
 		}
 		hash_object(buf.buf, type, no_filters ? NULL : buf.buf, flags,
 			    literally);
 	}
 	strbuf_release(&buf);
-	strbuf_release(&nbuf);
+	strbuf_release(&unquoted);
 }
 
 int cmd_hash_object(int argc, const char **argv, const char *prefix)
 {
 	static const char * const hash_object_usage[] = {
 		N_("git hash-object [-t <type>] [-w] [--path=<file> | --no-filters] [--stdin] [--] <file>..."),
