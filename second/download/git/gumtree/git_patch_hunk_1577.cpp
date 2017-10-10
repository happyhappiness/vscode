 
 	string_list_clear(&needs_pushing, 0);
 
 	return ret;
 }
 
-static int is_submodule_commit_present(const char *path, unsigned char sha1[20])
+static int append_oid_to_array(const char *ref, const struct object_id *oid,
+			       int flags, void *data)
 {
-	int is_present = 0;
-	if (!add_submodule_odb(path) && lookup_commit_reference(sha1)) {
-		/* Even if the submodule is checked out and the commit is
-		 * present, make sure it is reachable from a ref. */
-		struct child_process cp = CHILD_PROCESS_INIT;
-		const char *argv[] = {"rev-list", "-n", "1", NULL, "--not", "--all", NULL};
-		struct strbuf buf = STRBUF_INIT;
-
-		argv[3] = sha1_to_hex(sha1);
-		cp.argv = argv;
-		prepare_submodule_repo_env(&cp.env_array);
-		cp.git_cmd = 1;
-		cp.no_stdin = 1;
-		cp.dir = path;
-		if (!capture_command(&cp, &buf, 1024) && !buf.len)
-			is_present = 1;
-
-		strbuf_release(&buf);
-	}
-	return is_present;
-}
-
-static void submodule_collect_changed_cb(struct diff_queue_struct *q,
-					 struct diff_options *options,
-					 void *data)
-{
-	int i;
-	for (i = 0; i < q->nr; i++) {
-		struct diff_filepair *p = q->queue[i];
-		if (!S_ISGITLINK(p->two->mode))
-			continue;
-
-		if (S_ISGITLINK(p->one->mode)) {
-			/* NEEDSWORK: We should honor the name configured in
-			 * the .gitmodules file of the commit we are examining
-			 * here to be able to correctly follow submodules
-			 * being moved around. */
-			struct string_list_item *path;
-			path = unsorted_string_list_lookup(&changed_submodule_paths, p->two->path);
-			if (!path && !is_submodule_commit_present(p->two->path, p->two->oid.hash))
-				string_list_append(&changed_submodule_paths, xstrdup(p->two->path));
-		} else {
-			/* Submodule is new or was moved here */
-			/* NEEDSWORK: When the .git directories of submodules
-			 * live inside the superprojects .git directory some
-			 * day we should fetch new submodules directly into
-			 * that location too when config or options request
-			 * that so they can be checked out from there. */
-			continue;
-		}
-	}
-}
-
-static int add_sha1_to_array(const char *ref, const struct object_id *oid,
-			     int flags, void *data)
-{
-	oid_array_append(data, oid);
+	struct oid_array *array = data;
+	oid_array_append(array, oid);
 	return 0;
 }
 
 void check_for_new_submodule_commits(struct object_id *oid)
 {
 	if (!initialized_fetch_ref_tips) {
-		for_each_ref(add_sha1_to_array, &ref_tips_before_fetch);
+		for_each_ref(append_oid_to_array, &ref_tips_before_fetch);
 		initialized_fetch_ref_tips = 1;
 	}
 
 	oid_array_append(&ref_tips_after_fetch, oid);
 }
 
-static int add_oid_to_argv(const struct object_id *oid, void *data)
-{
-	argv_array_push(data, oid_to_hex(oid));
-	return 0;
-}
-
 static void calculate_changed_submodule_paths(void)
 {
-	struct rev_info rev;
-	struct commit *commit;
 	struct argv_array argv = ARGV_ARRAY_INIT;
+	struct string_list changed_submodules = STRING_LIST_INIT_DUP;
+	const struct string_list_item *item;
 
 	/* No need to check if there are no submodules configured */
 	if (!submodule_from_path(NULL, NULL))
 		return;
 
-	init_revisions(&rev, NULL);
 	argv_array_push(&argv, "--"); /* argv[0] program name */
 	oid_array_for_each_unique(&ref_tips_after_fetch,
-				   add_oid_to_argv, &argv);
+				   append_oid_to_argv, &argv);
 	argv_array_push(&argv, "--not");
 	oid_array_for_each_unique(&ref_tips_before_fetch,
-				   add_oid_to_argv, &argv);
-	setup_revisions(argv.argc, argv.argv, &rev, NULL);
-	if (prepare_revision_walk(&rev))
-		die("revision walk setup failed");
+				   append_oid_to_argv, &argv);
 
 	/*
 	 * Collect all submodules (whether checked out or not) for which new
 	 * commits have been recorded upstream in "changed_submodule_paths".
 	 */
-	while ((commit = get_revision(&rev))) {
-		struct commit_list *parent = commit->parents;
-		while (parent) {
-			struct diff_options diff_opts;
-			diff_setup(&diff_opts);
-			DIFF_OPT_SET(&diff_opts, RECURSIVE);
-			diff_opts.output_format |= DIFF_FORMAT_CALLBACK;
-			diff_opts.format_callback = submodule_collect_changed_cb;
-			diff_setup_done(&diff_opts);
-			diff_tree_sha1(parent->item->object.oid.hash, commit->object.oid.hash, "", &diff_opts);
-			diffcore_std(&diff_opts);
-			diff_flush(&diff_opts);
-			parent = parent->next;
-		}
+	collect_changed_submodules(&changed_submodules, &argv);
+
+	for_each_string_list_item(item, &changed_submodules) {
+		struct oid_array *commits = item->util;
+		const char *path = item->string;
+
+		if (!submodule_has_commits(path, commits))
+			string_list_append(&changed_submodule_paths, path);
 	}
 
+	free_submodules_oids(&changed_submodules);
 	argv_array_clear(&argv);
 	oid_array_clear(&ref_tips_before_fetch);
 	oid_array_clear(&ref_tips_after_fetch);
 	initialized_fetch_ref_tips = 0;
 }
 
+int submodule_touches_in_range(struct object_id *excl_oid,
+			       struct object_id *incl_oid)
+{
+	struct string_list subs = STRING_LIST_INIT_DUP;
+	struct argv_array args = ARGV_ARRAY_INIT;
+	int ret;
+
+	gitmodules_config();
+	/* No need to check if there are no submodules configured */
+	if (!submodule_from_path(NULL, NULL))
+		return 0;
+
+	argv_array_push(&args, "--"); /* args[0] program name */
+	argv_array_push(&args, oid_to_hex(incl_oid));
+	argv_array_push(&args, "--not");
+	argv_array_push(&args, oid_to_hex(excl_oid));
+
+	collect_changed_submodules(&subs, &args);
+	ret = subs.nr;
+
+	argv_array_clear(&args);
+
+	free_submodules_oids(&subs);
+	return ret;
+}
+
 struct submodule_parallel_fetch {
 	int count;
 	struct argv_array args;
 	const char *work_tree;
 	const char *prefix;
 	int command_line_option;
