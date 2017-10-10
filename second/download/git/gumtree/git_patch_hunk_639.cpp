 static int has_remote(const char *refname, const struct object_id *oid,
 		      int flags, void *cb_data)
 {
 	return 1;
 }
 
-static int submodule_needs_pushing(const char *path, const unsigned char sha1[20])
+static int append_sha1_to_argv(const unsigned char sha1[20], void *data)
 {
-	if (add_submodule_odb(path) || !lookup_commit_reference(sha1))
+	struct argv_array *argv = data;
+	argv_array_push(argv, sha1_to_hex(sha1));
+	return 0;
+}
+
+static int check_has_commit(const unsigned char sha1[20], void *data)
+{
+	int *has_commit = data;
+
+	if (!lookup_commit_reference(sha1))
+		*has_commit = 0;
+
+	return 0;
+}
+
+static int submodule_has_commits(const char *path, struct sha1_array *commits)
+{
+	int has_commit = 1;
+
+	if (add_submodule_odb(path))
+		return 0;
+
+	sha1_array_for_each_unique(commits, check_has_commit, &has_commit);
+	return has_commit;
+}
+
+static int submodule_needs_pushing(const char *path, struct sha1_array *commits)
+{
+	if (!submodule_has_commits(path, commits))
+		/*
+		 * NOTE: We do consider it safe to return "no" here. The
+		 * correct answer would be "We do not know" instead of
+		 * "No push needed", but it is quite hard to change
+		 * the submodule pointer without having the submodule
+		 * around. If a user did however change the submodules
+		 * without having the submodule around, this indicates
+		 * an expert who knows what they are doing or a
+		 * maintainer integrating work from other people. In
+		 * both cases it should be safe to skip this check.
+		 */
 		return 0;
 
 	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
 		struct child_process cp = CHILD_PROCESS_INIT;
-		const char *argv[] = {"rev-list", NULL, "--not", "--remotes", "-n", "1" , NULL};
 		struct strbuf buf = STRBUF_INIT;
 		int needs_pushing = 0;
 
-		argv[1] = sha1_to_hex(sha1);
-		cp.argv = argv;
+		argv_array_push(&cp.args, "rev-list");
+		sha1_array_for_each_unique(commits, append_sha1_to_argv, &cp.args);
+		argv_array_pushl(&cp.args, "--not", "--remotes", "-n", "1" , NULL);
+
 		prepare_submodule_repo_env(&cp.env_array);
 		cp.git_cmd = 1;
 		cp.no_stdin = 1;
 		cp.out = -1;
 		cp.dir = path;
 		if (start_command(&cp))
-			die("Could not run 'git rev-list %s --not --remotes -n 1' command in submodule %s",
-				sha1_to_hex(sha1), path);
+			die("Could not run 'git rev-list <commits> --not --remotes -n 1' command in submodule %s",
+					path);
 		if (strbuf_read(&buf, cp.out, 41))
 			needs_pushing = 1;
 		finish_command(&cp);
 		close(cp.out);
 		strbuf_release(&buf);
 		return needs_pushing;
 	}
 
 	return 0;
 }
 
+static struct sha1_array *submodule_commits(struct string_list *submodules,
+					    const char *path)
+{
+	struct string_list_item *item;
+
+	item = string_list_insert(submodules, path);
+	if (item->util)
+		return (struct sha1_array *) item->util;
+
+	/* NEEDSWORK: should we have sha1_array_init()? */
+	item->util = xcalloc(1, sizeof(struct sha1_array));
+	return (struct sha1_array *) item->util;
+}
+
 static void collect_submodules_from_diff(struct diff_queue_struct *q,
 					 struct diff_options *options,
 					 void *data)
 {
 	int i;
-	struct string_list *needs_pushing = data;
+	struct string_list *submodules = data;
 
 	for (i = 0; i < q->nr; i++) {
 		struct diff_filepair *p = q->queue[i];
+		struct sha1_array *commits;
 		if (!S_ISGITLINK(p->two->mode))
 			continue;
-		if (submodule_needs_pushing(p->two->path, p->two->oid.hash))
-			string_list_insert(needs_pushing, p->two->path);
+		commits = submodule_commits(submodules, p->two->path);
+		sha1_array_append(commits, p->two->oid.hash);
 	}
 }
 
 static void find_unpushed_submodule_commits(struct commit *commit,
 		struct string_list *needs_pushing)
 {
