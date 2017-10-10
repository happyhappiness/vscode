 		return needs_pushing;
 	}
 
 	return 0;
 }
 
-static struct oid_array *submodule_commits(struct string_list *submodules,
-					    const char *path)
-{
-	struct string_list_item *item;
-
-	item = string_list_insert(submodules, path);
-	if (item->util)
-		return (struct oid_array *) item->util;
-
-	/* NEEDSWORK: should we have oid_array_init()? */
-	item->util = xcalloc(1, sizeof(struct oid_array));
-	return (struct oid_array *) item->util;
-}
-
-static void collect_submodules_from_diff(struct diff_queue_struct *q,
-					 struct diff_options *options,
-					 void *data)
-{
-	int i;
-	struct string_list *submodules = data;
-
-	for (i = 0; i < q->nr; i++) {
-		struct diff_filepair *p = q->queue[i];
-		struct oid_array *commits;
-		if (!S_ISGITLINK(p->two->mode))
-			continue;
-		commits = submodule_commits(submodules, p->two->path);
-		oid_array_append(commits, &p->two->oid);
-	}
-}
-
-static void find_unpushed_submodule_commits(struct commit *commit,
-		struct string_list *needs_pushing)
-{
-	struct rev_info rev;
-
-	init_revisions(&rev, NULL);
-	rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
-	rev.diffopt.format_callback = collect_submodules_from_diff;
-	rev.diffopt.format_callback_data = needs_pushing;
-	diff_tree_combined_merge(commit, 1, &rev);
-}
-
-static void free_submodules_sha1s(struct string_list *submodules)
-{
-	struct string_list_item *item;
-	for_each_string_list_item(item, submodules)
-		oid_array_clear((struct oid_array *) item->util);
-	string_list_clear(submodules, 1);
-}
-
 int find_unpushed_submodules(struct oid_array *commits,
 		const char *remotes_name, struct string_list *needs_pushing)
 {
-	struct rev_info rev;
-	struct commit *commit;
 	struct string_list submodules = STRING_LIST_INIT_DUP;
 	struct string_list_item *submodule;
 	struct argv_array argv = ARGV_ARRAY_INIT;
 
-	init_revisions(&rev, NULL);
-
 	/* argv.argv[0] will be ignored by setup_revisions */
 	argv_array_push(&argv, "find_unpushed_submodules");
 	oid_array_for_each_unique(commits, append_oid_to_argv, &argv);
 	argv_array_push(&argv, "--not");
 	argv_array_pushf(&argv, "--remotes=%s", remotes_name);
 
-	setup_revisions(argv.argc, argv.argv, &rev, NULL);
-	if (prepare_revision_walk(&rev))
-		die("revision walk setup failed");
-
-	while ((commit = get_revision(&rev)) != NULL)
-		find_unpushed_submodule_commits(commit, &submodules);
-
-	reset_revision_walk();
-	argv_array_clear(&argv);
+	collect_changed_submodules(&submodules, &argv);
 
 	for_each_string_list_item(submodule, &submodules) {
-		struct oid_array *commits = (struct oid_array *) submodule->util;
+		struct oid_array *commits = submodule->util;
+		const char *path = submodule->string;
 
-		if (submodule_needs_pushing(submodule->string, commits))
-			string_list_insert(needs_pushing, submodule->string);
+		if (submodule_needs_pushing(path, commits))
+			string_list_insert(needs_pushing, path);
 	}
-	free_submodules_sha1s(&submodules);
+
+	free_submodules_oids(&submodules);
+	argv_array_clear(&argv);
 
 	return needs_pushing->nr;
 }
 
 static int push_submodule(const char *path,
 			  const struct remote *remote,
