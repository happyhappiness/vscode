 static const char *tag_other = "";
 static const char *tag_killed = "";
 static const char *tag_modified = "";
 static const char *tag_skip_worktree = "";
 static const char *tag_resolve_undo = "";
 
+static void write_eolinfo(const struct cache_entry *ce, const char *path)
+{
+	if (!show_eol)
+		return;
+	else {
+		struct stat st;
+		const char *i_txt = "";
+		const char *w_txt = "";
+		const char *a_txt = get_convert_attr_ascii(path);
+		if (ce && S_ISREG(ce->ce_mode))
+			i_txt = get_cached_convert_stats_ascii(ce->name);
+		if (!lstat(path, &st) && S_ISREG(st.st_mode))
+			w_txt = get_wt_convert_stats_ascii(path);
+		printf("i/%-5s w/%-5s attr/%-17s\t", i_txt, w_txt, a_txt);
+	}
+}
+
 static void write_name(const char *name)
 {
 	/*
 	 * With "--full-name", prefix_len=0; this caller needs to pass
 	 * an empty string in that case (a NULL is good for "").
 	 */
