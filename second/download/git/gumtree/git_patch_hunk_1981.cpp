 
 	si->shallow_ref[cmd->index] = 0;
 	sha1_array_clear(&extra);
 	return 0;
 }
 
+static const char *update_worktree(unsigned char *sha1)
+{
+	const char *update_refresh[] = {
+		"update-index", "-q", "--ignore-submodules", "--refresh", NULL
+	};
+	const char *diff_files[] = {
+		"diff-files", "--quiet", "--ignore-submodules", "--", NULL
+	};
+	const char *diff_index[] = {
+		"diff-index", "--quiet", "--cached", "--ignore-submodules",
+		"HEAD", "--", NULL
+	};
+	const char *read_tree[] = {
+		"read-tree", "-u", "-m", NULL, NULL
+	};
+	const char *work_tree = git_work_tree_cfg ? git_work_tree_cfg : "..";
+	struct argv_array env = ARGV_ARRAY_INIT;
+	struct child_process child = CHILD_PROCESS_INIT;
+
+	if (is_bare_repository())
+		return "denyCurrentBranch = updateInstead needs a worktree";
+
+	argv_array_pushf(&env, "GIT_DIR=%s", absolute_path(get_git_dir()));
+
+	child.argv = update_refresh;
+	child.env = env.argv;
+	child.dir = work_tree;
+	child.no_stdin = 1;
+	child.stdout_to_stderr = 1;
+	child.git_cmd = 1;
+	if (run_command(&child)) {
+		argv_array_clear(&env);
+		return "Up-to-date check failed";
+	}
+
+	/* run_command() does not clean up completely; reinitialize */
+	child_process_init(&child);
+	child.argv = diff_files;
+	child.env = env.argv;
+	child.dir = work_tree;
+	child.no_stdin = 1;
+	child.stdout_to_stderr = 1;
+	child.git_cmd = 1;
+	if (run_command(&child)) {
+		argv_array_clear(&env);
+		return "Working directory has unstaged changes";
+	}
+
+	child_process_init(&child);
+	child.argv = diff_index;
+	child.env = env.argv;
+	child.no_stdin = 1;
+	child.no_stdout = 1;
+	child.stdout_to_stderr = 0;
+	child.git_cmd = 1;
+	if (run_command(&child)) {
+		argv_array_clear(&env);
+		return "Working directory has staged changes";
+	}
+
+	read_tree[3] = sha1_to_hex(sha1);
+	child_process_init(&child);
+	child.argv = read_tree;
+	child.env = env.argv;
+	child.dir = work_tree;
+	child.no_stdin = 1;
+	child.no_stdout = 1;
+	child.stdout_to_stderr = 0;
+	child.git_cmd = 1;
+	if (run_command(&child)) {
+		argv_array_clear(&env);
+		return "Could not update working tree to new HEAD";
+	}
+
+	argv_array_clear(&env);
+	return NULL;
+}
+
 static const char *update(struct command *cmd, struct shallow_info *si)
 {
 	const char *name = cmd->ref_name;
 	struct strbuf namespaced_name_buf = STRBUF_INIT;
-	const char *namespaced_name;
+	const char *namespaced_name, *ret;
 	unsigned char *old_sha1 = cmd->old_sha1;
 	unsigned char *new_sha1 = cmd->new_sha1;
 
 	/* only refs/... are allowed */
 	if (!starts_with(name, "refs/") || check_refname_format(name + 5, 0)) {
 		rp_error("refusing to create funny ref '%s' remotely", name);
