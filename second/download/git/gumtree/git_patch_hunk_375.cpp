 		die(_("revision walk setup failed"));
 	/*
 	 * Traverse the commits list, get prerequisite patch ids
 	 * and stuff them in bases structure.
 	 */
 	while ((commit = get_revision(&revs)) != NULL) {
-		unsigned char sha1[20];
+		struct object_id oid;
 		struct object_id *patch_id;
 		if (commit->util)
 			continue;
-		if (commit_patch_id(commit, &diffopt, sha1, 0))
+		if (commit_patch_id(commit, &diffopt, oid.hash, 0))
 			die(_("cannot get patch id"));
 		ALLOC_GROW(bases->patch_id, bases->nr_patch_id + 1, bases->alloc_patch_id);
 		patch_id = bases->patch_id + bases->nr_patch_id;
-		hashcpy(patch_id->hash, sha1);
+		oidcpy(patch_id, &oid);
 		bases->nr_patch_id++;
 	}
 }
 
 static void print_bases(struct base_tree_info *bases, FILE *file)
 {
