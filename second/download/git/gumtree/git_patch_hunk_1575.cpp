 	if (!should_update_submodules())
 		return NULL;
 
 	return submodule_from_path(null_sha1, ce->name);
 }
 
+static struct oid_array *submodule_commits(struct string_list *submodules,
+					   const char *path)
+{
+	struct string_list_item *item;
+
+	item = string_list_insert(submodules, path);
+	if (item->util)
+		return (struct oid_array *) item->util;
+
+	/* NEEDSWORK: should we have oid_array_init()? */
+	item->util = xcalloc(1, sizeof(struct oid_array));
+	return (struct oid_array *) item->util;
+}
+
+static void collect_changed_submodules_cb(struct diff_queue_struct *q,
+					  struct diff_options *options,
+					  void *data)
+{
+	int i;
+	struct string_list *changed = data;
+
+	for (i = 0; i < q->nr; i++) {
+		struct diff_filepair *p = q->queue[i];
+		struct oid_array *commits;
+		if (!S_ISGITLINK(p->two->mode))
+			continue;
+
+		if (S_ISGITLINK(p->one->mode)) {
+			/*
+			 * NEEDSWORK: We should honor the name configured in
+			 * the .gitmodules file of the commit we are examining
+			 * here to be able to correctly follow submodules
+			 * being moved around.
+			 */
+			commits = submodule_commits(changed, p->two->path);
+			oid_array_append(commits, &p->two->oid);
+		} else {
+			/* Submodule is new or was moved here */
+			/*
+			 * NEEDSWORK: When the .git directories of submodules
+			 * live inside the superprojects .git directory some
+			 * day we should fetch new submodules directly into
+			 * that location too when config or options request
+			 * that so they can be checked out from there.
+			 */
+			continue;
+		}
+	}
+}
+
+/*
+ * Collect the paths of submodules in 'changed' which have changed based on
+ * the revisions as specified in 'argv'.  Each entry in 'changed' will also
+ * have a corresponding 'struct oid_array' (in the 'util' field) which lists
+ * what the submodule pointers were updated to during the change.
+ */
+static void collect_changed_submodules(struct string_list *changed,
+				       struct argv_array *argv)
+{
+	struct rev_info rev;
+	const struct commit *commit;
+
+	init_revisions(&rev, NULL);
+	setup_revisions(argv->argc, argv->argv, &rev, NULL);
+	if (prepare_revision_walk(&rev))
+		die("revision walk setup failed");
+
+	while ((commit = get_revision(&rev))) {
+		struct rev_info diff_rev;
+
+		init_revisions(&diff_rev, NULL);
+		diff_rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
+		diff_rev.diffopt.format_callback = collect_changed_submodules_cb;
+		diff_rev.diffopt.format_callback_data = changed;
+		diff_tree_combined_merge(commit, 1, &diff_rev);
+	}
+
+	reset_revision_walk();
+}
+
+static void free_submodules_oids(struct string_list *submodules)
+{
+	struct string_list_item *item;
+	for_each_string_list_item(item, submodules)
+		oid_array_clear((struct oid_array *) item->util);
+	string_list_clear(submodules, 1);
+}
+
 static int has_remote(const char *refname, const struct object_id *oid,
 		      int flags, void *cb_data)
 {
 	return 1;
 }
 
