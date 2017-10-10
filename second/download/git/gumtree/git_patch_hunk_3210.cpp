 	struct utsname uts;
 
 	if (sb.len)
 		return sb.buf;
 	if (uname(&uts) < 0)
 		die_errno(_("failed to get kernel name and information"));
-	strbuf_addf(&sb, "Location %s, system %s %s %s", get_git_work_tree(),
-		    uts.sysname, uts.release, uts.version);
+	strbuf_addf(&sb, "Location %s, system %s", get_git_work_tree(),
+		    uts.sysname);
 	return sb.buf;
 }
 
 static int ident_in_untracked(const struct untracked_cache *uc)
 {
-	const char *end = uc->ident.buf + uc->ident.len;
-	const char *p   = uc->ident.buf;
+	/*
+	 * Previous git versions may have saved many NUL separated
+	 * strings in the "ident" field, but it is insane to manage
+	 * many locations, so just take care of the first one.
+	 */
 
-	for (p = uc->ident.buf; p < end; p += strlen(p) + 1)
-		if (!strcmp(p, get_ident_string()))
-			return 1;
-	return 0;
+	return !strcmp(uc->ident.buf, get_ident_string());
 }
 
-void add_untracked_ident(struct untracked_cache *uc)
+static void set_untracked_ident(struct untracked_cache *uc)
 {
-	if (ident_in_untracked(uc))
-		return;
+	strbuf_reset(&uc->ident);
 	strbuf_addstr(&uc->ident, get_ident_string());
-	/* this strbuf contains a list of strings, save NUL too */
+
+	/*
+	 * This strbuf used to contain a list of NUL separated
+	 * strings, so save NUL too for backward compatibility.
+	 */
 	strbuf_addch(&uc->ident, 0);
 }
 
+static void new_untracked_cache(struct index_state *istate)
+{
+	struct untracked_cache *uc = xcalloc(1, sizeof(*uc));
+	strbuf_init(&uc->ident, 100);
+	uc->exclude_per_dir = ".gitignore";
+	/* should be the same flags used by git-status */
+	uc->dir_flags = DIR_SHOW_OTHER_DIRECTORIES | DIR_HIDE_EMPTY_DIRECTORIES;
+	set_untracked_ident(uc);
+	istate->untracked = uc;
+	istate->cache_changed |= UNTRACKED_CHANGED;
+}
+
+void add_untracked_cache(struct index_state *istate)
+{
+	if (!istate->untracked) {
+		new_untracked_cache(istate);
+	} else {
+		if (!ident_in_untracked(istate->untracked)) {
+			free_untracked_cache(istate->untracked);
+			new_untracked_cache(istate);
+		}
+	}
+}
+
+void remove_untracked_cache(struct index_state *istate)
+{
+	if (istate->untracked) {
+		free_untracked_cache(istate->untracked);
+		istate->untracked = NULL;
+		istate->cache_changed |= UNTRACKED_CHANGED;
+	}
+}
+
 static struct untracked_cache_dir *validate_untracked_cache(struct dir_struct *dir,
 						      int base_len,
 						      const struct pathspec *pathspec)
 {
 	struct untracked_cache_dir *root;
 
