 	FILE *fp;
 	struct strbuf sb = STRBUF_INIT;
 	unsigned char sha1[GIT_SHA1_RAWSZ];
 
 	if (!(fp = fopen(filename, "r")))
 		die_errno(_("could not open '%s' for reading"), filename);
-	while (strbuf_getline(&sb, fp, '\n') != EOF) {
+	while (strbuf_getline_lf(&sb, fp) != EOF) {
 		if (get_sha1_hex(sb.buf, sha1))
 			continue;  /* invalid line: does not start with SHA1 */
 		if (starts_with(sb.buf + GIT_SHA1_HEXSZ, "\tnot-for-merge\t"))
 			continue;  /* ref is not-for-merge */
 		sha1_array_append(merge_heads, sha1);
 	}
