 	cb->warned_bad_reflog = 0;
 	cb->name_for_errormsg = path;
 	for_each_reflog_ent(path, handle_one_reflog_ent, cb_data);
 	return 0;
 }
 
-static void handle_reflog(struct rev_info *revs, unsigned flags)
+void add_reflogs_to_pending(struct rev_info *revs, unsigned flags)
 {
 	struct all_refs_cb cb;
 	cb.all_revs = revs;
 	cb.all_flags = flags;
 	for_each_reflog(handle_one_reflog, &cb);
 }
 
+static void add_cache_tree(struct cache_tree *it, struct rev_info *revs,
+			   struct strbuf *path)
+{
+	size_t baselen = path->len;
+	int i;
+
+	if (it->entry_count >= 0) {
+		struct tree *tree = lookup_tree(it->sha1);
+		add_pending_object_with_path(revs, &tree->object, "",
+					     040000, path->buf);
+	}
+
+	for (i = 0; i < it->subtree_nr; i++) {
+		struct cache_tree_sub *sub = it->down[i];
+		strbuf_addf(path, "%s%s", baselen ? "/" : "", sub->name);
+		add_cache_tree(sub->cache_tree, revs, path);
+		strbuf_setlen(path, baselen);
+	}
+
+}
+
+void add_index_objects_to_pending(struct rev_info *revs, unsigned flags)
+{
+	int i;
+
+	read_cache();
+	for (i = 0; i < active_nr; i++) {
+		struct cache_entry *ce = active_cache[i];
+		struct blob *blob;
+
+		if (S_ISGITLINK(ce->ce_mode))
+			continue;
+
+		blob = lookup_blob(ce->sha1);
+		if (!blob)
+			die("unable to add index blob to traversal");
+		add_pending_object_with_path(revs, &blob->object, "",
+					     ce->ce_mode, ce->name);
+	}
+
+	if (active_cache_tree) {
+		struct strbuf path = STRBUF_INIT;
+		add_cache_tree(active_cache_tree, revs, &path);
+		strbuf_release(&path);
+	}
+}
+
 static int add_parents_only(struct rev_info *revs, const char *arg_, int flags)
 {
 	unsigned char sha1[20];
 	struct object *it;
 	struct commit *commit;
 	struct commit_list *parents;
