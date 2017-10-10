  * message suitable for parsing with git-mailinfo.
  */
 static int hg_patch_to_mail(FILE *out, FILE *in, int keep_cr)
 {
 	struct strbuf sb = STRBUF_INIT;
 
-	while (!strbuf_getline(&sb, in, '\n')) {
+	while (!strbuf_getline_lf(&sb, in)) {
 		const char *str;
 
 		if (skip_prefix(sb.buf, "# User ", &str))
 			fprintf(out, "From: %s\n", str);
 		else if (skip_prefix(sb.buf, "# Date ", &str)) {
 			unsigned long timestamp;
