 	c = init_copy_notes_for_rewrite("rebase");
 	if (!c)
 		return 0;
 
 	fp = xfopen(am_path(state, "rewritten"), "r");
 
-	while (!strbuf_getline(&sb, fp, '\n')) {
+	while (!strbuf_getline_lf(&sb, fp)) {
 		unsigned char from_obj[GIT_SHA1_RAWSZ], to_obj[GIT_SHA1_RAWSZ];
 
 		if (sb.len != GIT_SHA1_HEXSZ * 2 + 1) {
 			ret = error(invalid_line, sb.buf);
 			goto finish;
 		}
