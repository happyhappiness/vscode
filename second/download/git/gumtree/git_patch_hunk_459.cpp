 
 static int similarity_index(struct diff_filepair *p)
 {
 	return p->score * 100 / MAX_SCORE;
 }
 
+static const char *diff_abbrev_oid(const struct object_id *oid, int abbrev)
+{
+	if (startup_info->have_repository)
+		return find_unique_abbrev(oid->hash, abbrev);
+	else {
+		char *hex = oid_to_hex(oid);
+		if (abbrev < 0)
+			abbrev = FALLBACK_DEFAULT_ABBREV;
+		if (abbrev > GIT_SHA1_HEXSZ)
+			die("BUG: oid abbreviation out of range: %d", abbrev);
+		hex[abbrev] = '\0';
+		return hex;
+	}
+}
+
 static void fill_metainfo(struct strbuf *msg,
 			  const char *name,
 			  const char *other,
 			  struct diff_filespec *one,
 			  struct diff_filespec *two,
 			  struct diff_options *o,
