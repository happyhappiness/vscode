 
 	if (o->subtree_shift) {
 		merge = shift_tree_object(head, merge, o->subtree_shift);
 		common = shift_tree_object(head, common, o->subtree_shift);
 	}
 
-	if (sha_eq(common->object.sha1, merge->object.sha1)) {
+	if (sha_eq(common->object.oid.hash, merge->object.oid.hash)) {
 		output(o, 0, _("Already up-to-date!"));
 		*result = head;
 		return 1;
 	}
 
 	code = git_merge_trees(o->call_depth, common, head, merge);
 
 	if (code != 0) {
 		if (show(o, 4) || o->call_depth)
 			die(_("merging of trees %s and %s failed"),
-			    sha1_to_hex(head->object.sha1),
-			    sha1_to_hex(merge->object.sha1));
+			    oid_to_hex(&head->object.oid),
+			    oid_to_hex(&merge->object.oid));
 		else
 			exit(128);
 	}
 
 	if (unmerged_cache()) {
 		struct string_list *entries, *re_head, *re_merge;
