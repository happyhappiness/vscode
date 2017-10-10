 	 * likely to work fine when the automatic sizing of default
 	 * abbreviation length is used--we would be fed -1 in "len" in
 	 * that case, and will end up always appending three-dots, but
 	 * the automatic sizing is supposed to give abblen that ensures
 	 * uniqueness across all objects (statistically speaking).
 	 */
-	if (abblen < 37) {
-		static char hex[41];
+	if (abblen < GIT_SHA1_HEXSZ - 3) {
+		static char hex[GIT_SHA1_HEXSZ + 1];
 		if (len < abblen && abblen <= len + 2)
 			xsnprintf(hex, sizeof(hex), "%s%.*s", abbrev, len+3-abblen, "..");
 		else
 			xsnprintf(hex, sizeof(hex), "%s...", abbrev);
 		return hex;
 	}
-	return sha1_to_hex(sha1);
+
+	return oid_to_hex(oid);
 }
 
 static void diff_flush_raw(struct diff_filepair *p, struct diff_options *opt)
 {
 	int line_termination = opt->line_termination;
 	int inter_name_termination = line_termination ? '\t' : '\0';
 
 	fprintf(opt->file, "%s", diff_line_prefix(opt));
 	if (!(opt->output_format & DIFF_FORMAT_NAME_STATUS)) {
 		fprintf(opt->file, ":%06o %06o %s ", p->one->mode, p->two->mode,
-			diff_unique_abbrev(p->one->oid.hash, opt->abbrev));
+			diff_aligned_abbrev(&p->one->oid, opt->abbrev));
 		fprintf(opt->file, "%s ",
-			diff_unique_abbrev(p->two->oid.hash, opt->abbrev));
+			diff_aligned_abbrev(&p->two->oid, opt->abbrev));
 	}
 	if (p->score) {
 		fprintf(opt->file, "%c%03d%c", p->status, similarity_index(p),
 			inter_name_termination);
 	} else {
 		fprintf(opt->file, "%c%c", p->status, inter_name_termination);
