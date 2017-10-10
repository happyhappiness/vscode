 
 	return num_ignored;
 }
 
 static int check_ignore_stdin_paths(struct dir_struct *dir, const char *prefix)
 {
-	struct strbuf buf, nbuf;
+	struct strbuf buf = STRBUF_INIT;
+	struct strbuf unquoted = STRBUF_INIT;
 	char *pathspec[2] = { NULL, NULL };
-	int line_termination = nul_term_line ? 0 : '\n';
+	strbuf_getline_fn getline_fn;
 	int num_ignored = 0;
 
-	strbuf_init(&buf, 0);
-	strbuf_init(&nbuf, 0);
-	while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
-		if (line_termination && buf.buf[0] == '"') {
-			strbuf_reset(&nbuf);
-			if (unquote_c_style(&nbuf, buf.buf, NULL))
+	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
+	while (getline_fn(&buf, stdin) != EOF) {
+		if (!nul_term_line && buf.buf[0] == '"') {
+			strbuf_reset(&unquoted);
+			if (unquote_c_style(&unquoted, buf.buf, NULL))
 				die("line is badly quoted");
-			strbuf_swap(&buf, &nbuf);
+			strbuf_swap(&buf, &unquoted);
 		}
 		pathspec[0] = buf.buf;
 		num_ignored += check_ignore(dir, prefix,
 					    1, (const char **)pathspec);
 		maybe_flush_or_die(stdout, "check-ignore to stdout");
 	}
 	strbuf_release(&buf);
-	strbuf_release(&nbuf);
+	strbuf_release(&unquoted);
 	return num_ignored;
 }
 
 int cmd_check_ignore(int argc, const char **argv, const char *prefix)
 {
 	int num_ignored;
