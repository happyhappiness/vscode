 	 * the new symrefs.
 	 */
 	for_each_ref(read_remote_branches, &rename);
 	for (i = 0; i < remote_branches.nr; i++) {
 		struct string_list_item *item = remote_branches.items + i;
 		int flag = 0;
-		unsigned char sha1[20];
+		struct object_id oid;
 
-		read_ref_full(item->string, RESOLVE_REF_READING, sha1, &flag);
+		read_ref_full(item->string, RESOLVE_REF_READING, oid.hash, &flag);
 		if (!(flag & REF_ISSYMREF))
 			continue;
 		if (delete_ref(item->string, NULL, REF_NODEREF))
 			die(_("deleting '%s' failed"), item->string);
 	}
 	for (i = 0; i < remote_branches.nr; i++) {
