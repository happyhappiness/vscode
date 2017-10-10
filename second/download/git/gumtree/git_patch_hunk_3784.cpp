 
 	if (o->subtree_shift) {
 		merge = shift_tree_object(head, merge, o->subtree_shift);
 		common = shift_tree_object(head, common, o->subtree_shift);
 	}
 
-	if (sha_eq(common->object.oid.hash, merge->object.oid.hash)) {
+	if (oid_eq(&common->object.oid, &merge->object.oid)) {
 		output(o, 0, _("Already up-to-date!"));
 		*result = head;
 		return 1;
 	}
 
 	code = git_merge_trees(o->call_depth, common, head, merge);
 
 	if (code != 0) {
 		if (show(o, 4) || o->call_depth)
-			die(_("merging of trees %s and %s failed"),
+			err(o, _("merging of trees %s and %s failed"),
 			    oid_to_hex(&head->object.oid),
 			    oid_to_hex(&merge->object.oid));
-		else
-			exit(128);
+		return -1;
 	}
 
 	if (unmerged_cache()) {
 		struct string_list *entries, *re_head, *re_merge;
 		int i;
 		string_list_clear(&o->current_file_set, 1);
