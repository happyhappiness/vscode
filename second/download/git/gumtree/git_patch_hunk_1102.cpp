 	cp.git_cmd = 1;
 	cp.no_stdin = 1;
 	cp.out = -1;
 	cp.dir = path;
 	if (start_command(&cp)) {
 		if (flags & SUBMODULE_REMOVAL_DIE_ON_ERROR)
-			die(_("could not start 'git status in submodule '%s'"),
+			die(_("could not start 'git status' in submodule '%s'"),
 				path);
 		ret = -1;
 		goto out;
 	}
 
 	len = strbuf_read(&buf, cp.out, 1024);
 	if (len > 2)
 		ret = 1;
 	close(cp.out);
 
 	if (finish_command(&cp)) {
 		if (flags & SUBMODULE_REMOVAL_DIE_ON_ERROR)
-			die(_("could not run 'git status in submodule '%s'"),
+			die(_("could not run 'git status' in submodule '%s'"),
 				path);
 		ret = -1;
 	}
 out:
 	strbuf_release(&buf);
 	return ret;
 }
 
+static const char *get_super_prefix_or_empty(void)
+{
+	const char *s = get_super_prefix();
+	if (!s)
+		s = "";
+	return s;
+}
+
+static int submodule_has_dirty_index(const struct submodule *sub)
+{
+	struct child_process cp = CHILD_PROCESS_INIT;
+
+	prepare_submodule_repo_env_no_git_dir(&cp.env_array);
+
+	cp.git_cmd = 1;
+	argv_array_pushl(&cp.args, "diff-index", "--quiet",
+				   "--cached", "HEAD", NULL);
+	cp.no_stdin = 1;
+	cp.no_stdout = 1;
+	cp.dir = sub->path;
+	if (start_command(&cp))
+		die("could not recurse into submodule '%s'", sub->path);
+
+	return finish_command(&cp);
+}
+
+static void submodule_reset_index(const char *path)
+{
+	struct child_process cp = CHILD_PROCESS_INIT;
+	prepare_submodule_repo_env_no_git_dir(&cp.env_array);
+
+	cp.git_cmd = 1;
+	cp.no_stdin = 1;
+	cp.dir = path;
+
+	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
+				   get_super_prefix_or_empty(), path);
+	argv_array_pushl(&cp.args, "read-tree", "-u", "--reset", NULL);
+
+	argv_array_push(&cp.args, EMPTY_TREE_SHA1_HEX);
+
+	if (run_command(&cp))
+		die("could not reset submodule index");
+}
+
+/**
+ * Moves a submodule at a given path from a given head to another new head.
+ * For edge cases (a submodule coming into existence or removing a submodule)
+ * pass NULL for old or new respectively.
+ */
+int submodule_move_head(const char *path,
+			 const char *old,
+			 const char *new,
+			 unsigned flags)
+{
+	int ret = 0;
+	struct child_process cp = CHILD_PROCESS_INIT;
+	const struct submodule *sub;
+
+	sub = submodule_from_path(null_sha1, path);
+
+	if (!sub)
+		die("BUG: could not get submodule information for '%s'", path);
+
+	if (old && !(flags & SUBMODULE_MOVE_HEAD_FORCE)) {
+		/* Check if the submodule has a dirty index. */
+		if (submodule_has_dirty_index(sub))
+			return error(_("submodule '%s' has dirty index"), path);
+	}
+
+	if (!(flags & SUBMODULE_MOVE_HEAD_DRY_RUN)) {
+		if (old) {
+			if (!submodule_uses_gitfile(path))
+				absorb_git_dir_into_superproject("", path,
+					ABSORB_GITDIR_RECURSE_SUBMODULES);
+		} else {
+			struct strbuf sb = STRBUF_INIT;
+			strbuf_addf(&sb, "%s/modules/%s",
+				    get_git_common_dir(), sub->name);
+			connect_work_tree_and_git_dir(path, sb.buf);
+			strbuf_release(&sb);
+
+			/* make sure the index is clean as well */
+			submodule_reset_index(path);
+		}
+	}
+
+	prepare_submodule_repo_env_no_git_dir(&cp.env_array);
+
+	cp.git_cmd = 1;
+	cp.no_stdin = 1;
+	cp.dir = path;
+
+	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
+			get_super_prefix_or_empty(), path);
+	argv_array_pushl(&cp.args, "read-tree", NULL);
+
+	if (flags & SUBMODULE_MOVE_HEAD_DRY_RUN)
+		argv_array_push(&cp.args, "-n");
+	else
+		argv_array_push(&cp.args, "-u");
+
+	if (flags & SUBMODULE_MOVE_HEAD_FORCE)
+		argv_array_push(&cp.args, "--reset");
+	else
+		argv_array_push(&cp.args, "-m");
+
+	argv_array_push(&cp.args, old ? old : EMPTY_TREE_SHA1_HEX);
+	argv_array_push(&cp.args, new ? new : EMPTY_TREE_SHA1_HEX);
+
+	if (run_command(&cp)) {
+		ret = -1;
+		goto out;
+	}
+
+	if (!(flags & SUBMODULE_MOVE_HEAD_DRY_RUN)) {
+		if (new) {
+			struct child_process cp1 = CHILD_PROCESS_INIT;
+			/* also set the HEAD accordingly */
+			cp1.git_cmd = 1;
+			cp1.no_stdin = 1;
+			cp1.dir = path;
+
+			argv_array_pushl(&cp1.args, "update-ref", "HEAD", new, NULL);
+
+			if (run_command(&cp1)) {
+				ret = -1;
+				goto out;
+			}
+		} else {
+			struct strbuf sb = STRBUF_INIT;
+
+			strbuf_addf(&sb, "%s/.git", path);
+			unlink_or_warn(sb.buf);
+			strbuf_release(&sb);
+
+			if (is_empty_dir(path))
+				rmdir_or_warn(path);
+		}
+	}
+out:
+	return ret;
+}
+
 static int find_first_merges(struct object_array *result, const char *path,
 		struct commit *a, struct commit *b)
 {
 	int i, j;
 	struct object_array merges = OBJECT_ARRAY_INIT;
 	struct commit *commit;
