 
 	if (prepare_revision_walk(&revs))
 		die("revision walk setup failed");
 	mark_edges_uninteresting(&revs, show_edge);
 	traverse_commit_list(&revs, show_commit, show_object, NULL);
 
+	if (unpack_unreachable_expiration) {
+		revs.ignore_missing_links = 1;
+		if (add_unseen_recent_objects_to_traversal(&revs,
+				unpack_unreachable_expiration))
+			die("unable to add recent objects");
+		if (prepare_revision_walk(&revs))
+			die("revision walk setup failed");
+		traverse_commit_list(&revs, record_recent_commit,
+				     record_recent_object, NULL);
+	}
+
 	if (keep_unreachable)
 		add_objects_in_unpacked_packs(&revs);
 	if (unpack_unreachable)
 		loosen_unused_packed_objects(&revs);
+
+	sha1_array_clear(&recent_objects);
 }
 
 static int option_parse_index_version(const struct option *opt,
 				      const char *arg, int unset)
 {
 	char *c;
