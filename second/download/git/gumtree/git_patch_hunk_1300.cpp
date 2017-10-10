 static const char *tag_other = "";
 static const char *tag_killed = "";
 static const char *tag_modified = "";
 static const char *tag_skip_worktree = "";
 static const char *tag_resolve_undo = "";
 
-static void write_eolinfo(const struct cache_entry *ce, const char *path)
+static void write_eolinfo(const struct index_state *istate,
+			  const struct cache_entry *ce, const char *path)
 {
-	if (!show_eol)
-		return;
-	else {
+	if (show_eol) {
 		struct stat st;
 		const char *i_txt = "";
 		const char *w_txt = "";
 		const char *a_txt = get_convert_attr_ascii(path);
 		if (ce && S_ISREG(ce->ce_mode))
-			i_txt = get_cached_convert_stats_ascii(ce->name);
+			i_txt = get_cached_convert_stats_ascii(istate,
+							       ce->name);
 		if (!lstat(path, &st) && S_ISREG(st.st_mode))
 			w_txt = get_wt_convert_stats_ascii(path);
 		printf("i/%-5s w/%-5s attr/%-17s\t", i_txt, w_txt, a_txt);
 	}
 }
 
 static void write_name(const char *name)
 {
 	/*
-	 * Prepend the super_prefix to name to construct the full_name to be
-	 * written.
-	 */
-	struct strbuf full_name = STRBUF_INIT;
-	if (super_prefix) {
-		strbuf_addstr(&full_name, super_prefix);
-		strbuf_addstr(&full_name, name);
-		name = full_name.buf;
-	}
-
-	/*
 	 * With "--full-name", prefix_len=0; this caller needs to pass
 	 * an empty string in that case (a NULL is good for "").
 	 */
 	write_name_quoted_relative(name, prefix_len ? prefix : NULL,
 				   stdout, line_terminator);
+}
+
+static const char *get_tag(const struct cache_entry *ce, const char *tag)
+{
+	static char alttag[4];
+
+	if (tag && *tag && show_valid_bit && (ce->ce_flags & CE_VALID)) {
+		memcpy(alttag, tag, 3);
+
+		if (isalpha(tag[0])) {
+			alttag[0] = tolower(tag[0]);
+		} else if (tag[0] == '?') {
+			alttag[0] = '!';
+		} else {
+			alttag[0] = 'v';
+			alttag[1] = tag[0];
+			alttag[2] = ' ';
+			alttag[3] = 0;
+		}
+
+		tag = alttag;
+	}
 
-	strbuf_release(&full_name);
+	return tag;
+}
+
+static void print_debug(const struct cache_entry *ce)
+{
+	if (debug_mode) {
+		const struct stat_data *sd = &ce->ce_stat_data;
+
+		printf("  ctime: %d:%d\n", sd->sd_ctime.sec, sd->sd_ctime.nsec);
+		printf("  mtime: %d:%d\n", sd->sd_mtime.sec, sd->sd_mtime.nsec);
+		printf("  dev: %d\tino: %d\n", sd->sd_dev, sd->sd_ino);
+		printf("  uid: %d\tgid: %d\n", sd->sd_uid, sd->sd_gid);
+		printf("  size: %d\tflags: %x\n", sd->sd_size, ce->ce_flags);
+	}
 }
 
 static void show_dir_entry(const char *tag, struct dir_entry *ent)
 {
 	int len = max_prefix_len;
 
-	if (len >= ent->len)
+	if (len > ent->len)
 		die("git ls-files: internal error - directory entry not superset of prefix");
 
 	if (!dir_path_match(ent, &pathspec, len, ps_matched))
 		return;
 
 	fputs(tag, stdout);
-	write_eolinfo(NULL, ent->name);
+	write_eolinfo(NULL, NULL, ent->name);
 	write_name(ent->name);
 }
 
-static void show_other_files(struct dir_struct *dir)
+static void show_other_files(const struct index_state *istate,
+			     const struct dir_struct *dir)
 {
 	int i;
 
 	for (i = 0; i < dir->nr; i++) {
 		struct dir_entry *ent = dir->entries[i];
-		if (!cache_name_is_other(ent->name, ent->len))
+		if (!index_name_is_other(istate, ent->name, ent->len))
 			continue;
 		show_dir_entry(tag_other, ent);
 	}
 }
 
-static void show_killed_files(struct dir_struct *dir)
+static void show_killed_files(const struct index_state *istate,
+			      const struct dir_struct *dir)
 {
 	int i;
 	for (i = 0; i < dir->nr; i++) {
 		struct dir_entry *ent = dir->entries[i];
 		char *cp, *sp;
 		int pos, len, killed = 0;
