 	else if (!wt->id)
 		return get_git_common_dir();
 	else
 		return git_common_path("worktrees/%s", wt->id);
 }
 
+static struct worktree *find_worktree_by_suffix(struct worktree **list,
+						const char *suffix)
+{
+	struct worktree *found = NULL;
+	int nr_found = 0, suffixlen;
+
+	suffixlen = strlen(suffix);
+	if (!suffixlen)
+		return NULL;
+
+	for (; *list && nr_found < 2; list++) {
+		const char	*path	 = (*list)->path;
+		int		 pathlen = strlen(path);
+		int		 start	 = pathlen - suffixlen;
+
+		/* suffix must start at directory boundary */
+		if ((!start || (start > 0 && is_dir_sep(path[start - 1]))) &&
+		    !fspathcmp(suffix, path + start)) {
+			found = *list;
+			nr_found++;
+		}
+	}
+	return nr_found == 1 ? found : NULL;
+}
+
+struct worktree *find_worktree(struct worktree **list,
+			       const char *prefix,
+			       const char *arg)
+{
+	struct worktree *wt;
+	char *path;
+
+	if ((wt = find_worktree_by_suffix(list, arg)))
+		return wt;
+
+	arg = prefix_filename(prefix, strlen(prefix), arg);
+	path = xstrdup(real_path(arg));
+	for (; *list; list++)
+		if (!fspathcmp(path, real_path((*list)->path)))
+			break;
+	free(path);
+	return *list;
+}
+
+int is_main_worktree(const struct worktree *wt)
+{
+	return !wt->id;
+}
+
+const char *is_worktree_locked(struct worktree *wt)
+{
+	assert(!is_main_worktree(wt));
+
+	if (!wt->lock_reason_valid) {
+		struct strbuf path = STRBUF_INIT;
+
+		strbuf_addstr(&path, worktree_git_path(wt, "locked"));
+		if (file_exists(path.buf)) {
+			struct strbuf lock_reason = STRBUF_INIT;
+			if (strbuf_read_file(&lock_reason, path.buf, 0) < 0)
+				die_errno(_("failed to read '%s'"), path.buf);
+			strbuf_trim(&lock_reason);
+			wt->lock_reason = strbuf_detach(&lock_reason, NULL);
+		} else
+			wt->lock_reason = NULL;
+		wt->lock_reason_valid = 1;
+		strbuf_release(&path);
+	}
+
+	return wt->lock_reason;
+}
+
 int is_worktree_being_rebased(const struct worktree *wt,
 			      const char *target)
 {
 	struct wt_status_state state;
 	int found_rebase;
 
