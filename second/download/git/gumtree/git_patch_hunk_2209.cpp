 	if (cb_data.unique)
 		return cb_data.dst_ref;
 	free(cb_data.dst_ref);
 	return NULL;
 }
 
+static void check_linked_checkout(struct branch_info *new, const char *id)
+{
+	struct strbuf sb = STRBUF_INIT;
+	struct strbuf path = STRBUF_INIT;
+	struct strbuf gitdir = STRBUF_INIT;
+	const char *start, *end;
+
+	if (id)
+		strbuf_addf(&path, "%s/worktrees/%s/HEAD", get_git_common_dir(), id);
+	else
+		strbuf_addf(&path, "%s/HEAD", get_git_common_dir());
+
+	if (strbuf_read_file(&sb, path.buf, 0) < 0 ||
+	    !skip_prefix(sb.buf, "ref:", &start))
+		goto done;
+	while (isspace(*start))
+		start++;
+	end = start;
+	while (*end && !isspace(*end))
+		end++;
+	if (strncmp(start, new->path, end - start) || new->path[end - start] != '\0')
+		goto done;
+	if (id) {
+		strbuf_reset(&path);
+		strbuf_addf(&path, "%s/worktrees/%s/gitdir", get_git_common_dir(), id);
+		if (strbuf_read_file(&gitdir, path.buf, 0) <= 0)
+			goto done;
+		strbuf_rtrim(&gitdir);
+	} else
+		strbuf_addstr(&gitdir, get_git_common_dir());
+	die(_("'%s' is already checked out at '%s'"), new->name, gitdir.buf);
+done:
+	strbuf_release(&path);
+	strbuf_release(&sb);
+	strbuf_release(&gitdir);
+}
+
+static void check_linked_checkouts(struct branch_info *new)
+{
+	struct strbuf path = STRBUF_INIT;
+	DIR *dir;
+	struct dirent *d;
+
+	strbuf_addf(&path, "%s/worktrees", get_git_common_dir());
+	if ((dir = opendir(path.buf)) == NULL) {
+		strbuf_release(&path);
+		return;
+	}
+
+	/*
+	 * $GIT_COMMON_DIR/HEAD is practically outside
+	 * $GIT_DIR so resolve_ref_unsafe() won't work (it
+	 * uses git_path). Parse the ref ourselves.
+	 */
+	check_linked_checkout(new, NULL);
+
+	while ((d = readdir(dir)) != NULL) {
+		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
+			continue;
+		check_linked_checkout(new, d->d_name);
+	}
+	strbuf_release(&path);
+	closedir(dir);
+}
+
 static int parse_branchname_arg(int argc, const char **argv,
 				int dwim_new_local_branch_ok,
 				struct branch_info *new,
-				struct tree **source_tree,
-				unsigned char rev[20],
-				const char **new_branch)
+				struct checkout_opts *opts,
+				unsigned char rev[20])
 {
+	struct tree **source_tree = &opts->source_tree;
+	const char **new_branch = &opts->new_branch;
 	int argcount = 0;
 	unsigned char branch_rev[20];
 	const char *arg;
 	int dash_dash_pos;
 	int has_dash_dash = 0;
 	int i;
