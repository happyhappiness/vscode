  */
 static int stgit_patch_to_mail(FILE *out, FILE *in, int keep_cr)
 {
 	struct strbuf sb = STRBUF_INIT;
 	int subject_printed = 0;
 
-	while (!strbuf_getline(&sb, in, '\n')) {
+	while (!strbuf_getline_lf(&sb, in)) {
 		const char *str;
 
 		if (str_isspace(sb.buf))
 			continue;
 		else if (skip_prefix(sb.buf, "Author:", &str))
 			fprintf(out, "From:%s\n", str);
