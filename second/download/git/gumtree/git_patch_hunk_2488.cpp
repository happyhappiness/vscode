 	strbuf_release(&ref);
 	free(real_ref);
 }
 
 void remove_branch_state(void)
 {
-	unlink(git_path("CHERRY_PICK_HEAD"));
-	unlink(git_path("REVERT_HEAD"));
-	unlink(git_path("MERGE_HEAD"));
-	unlink(git_path("MERGE_RR"));
-	unlink(git_path("MERGE_MSG"));
-	unlink(git_path("MERGE_MODE"));
-	unlink(git_path("SQUASH_MSG"));
+	unlink(git_path_cherry_pick_head());
+	unlink(git_path_revert_head());
+	unlink(git_path_merge_head());
+	unlink(git_path_merge_rr());
+	unlink(git_path_merge_msg());
+	unlink(git_path_merge_mode());
+	unlink(git_path_squash_msg());
+}
+
+static char *find_linked_symref(const char *symref, const char *branch,
+				const char *id)
+{
+	struct strbuf sb = STRBUF_INIT;
+	struct strbuf path = STRBUF_INIT;
+	struct strbuf gitdir = STRBUF_INIT;
+	char *existing = NULL;
+
+	/*
+	 * $GIT_COMMON_DIR/$symref (e.g. HEAD) is practically outside
+	 * $GIT_DIR so resolve_ref_unsafe() won't work (it uses
+	 * git_path). Parse the ref ourselves.
+	 */
+	if (id)
+		strbuf_addf(&path, "%s/worktrees/%s/%s", get_git_common_dir(), id, symref);
+	else
+		strbuf_addf(&path, "%s/%s", get_git_common_dir(), symref);
+
+	if (!strbuf_readlink(&sb, path.buf, 0)) {
+		if (!starts_with(sb.buf, "refs/") ||
+		    check_refname_format(sb.buf, 0))
+			goto done;
+	} else if (strbuf_read_file(&sb, path.buf, 0) >= 0 &&
+	    starts_with(sb.buf, "ref:")) {
+		strbuf_remove(&sb, 0, strlen("ref:"));
+		strbuf_trim(&sb);
+	} else
+		goto done;
+	if (strcmp(sb.buf, branch))
+		goto done;
+	if (id) {
+		strbuf_reset(&path);
+		strbuf_addf(&path, "%s/worktrees/%s/gitdir", get_git_common_dir(), id);
+		if (strbuf_read_file(&gitdir, path.buf, 0) <= 0)
+			goto done;
+		strbuf_rtrim(&gitdir);
+	} else
+		strbuf_addstr(&gitdir, get_git_common_dir());
+	strbuf_strip_suffix(&gitdir, ".git");
+
+	existing = strbuf_detach(&gitdir, NULL);
+done:
+	strbuf_release(&path);
+	strbuf_release(&sb);
+	strbuf_release(&gitdir);
+
+	return existing;
+}
+
+char *find_shared_symref(const char *symref, const char *target)
+{
+	struct strbuf path = STRBUF_INIT;
+	DIR *dir;
+	struct dirent *d;
+	char *existing;
+
+	if ((existing = find_linked_symref(symref, target, NULL)))
+		return existing;
+
+	strbuf_addf(&path, "%s/worktrees", get_git_common_dir());
+	dir = opendir(path.buf);
+	strbuf_release(&path);
+	if (!dir)
+		return NULL;
+
+	while ((d = readdir(dir)) != NULL) {
+		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
+			continue;
+		existing = find_linked_symref(symref, target, d->d_name);
+		if (existing)
+			goto done;
+	}
+done:
+	closedir(dir);
+
+	return existing;
+}
+
+void die_if_checked_out(const char *branch)
+{
+	char *existing;
+
+	existing = find_shared_symref("HEAD", branch);
+	if (existing) {
+		skip_prefix(branch, "refs/heads/", &branch);
+		die(_("'%s' is already checked out at '%s'"), branch, existing);
+	}
 }
