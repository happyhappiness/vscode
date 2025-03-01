 
 	return conflicts ? -1 : 1;
 }
 
 int notes_merge(struct notes_merge_options *o,
 		struct notes_tree *local_tree,
-		unsigned char *result_sha1)
+		struct object_id *result_oid)
 {
-	unsigned char local_sha1[20], remote_sha1[20];
+	struct object_id local_oid, remote_oid;
 	struct commit *local, *remote;
 	struct commit_list *bases = NULL;
-	const unsigned char *base_sha1, *base_tree_sha1;
+	const struct object_id *base_oid, *base_tree_oid;
 	int result = 0;
 
 	assert(o->local_ref && o->remote_ref);
 	assert(!strcmp(o->local_ref, local_tree->ref));
-	hashclr(result_sha1);
+	oidclr(result_oid);
 
 	trace_printf("notes_merge(o->local_ref = %s, o->remote_ref = %s)\n",
 	       o->local_ref, o->remote_ref);
 
 	/* Dereference o->local_ref into local_sha1 */
-	if (read_ref_full(o->local_ref, 0, local_sha1, NULL))
+	if (read_ref_full(o->local_ref, 0, local_oid.hash, NULL))
 		die("Failed to resolve local notes ref '%s'", o->local_ref);
 	else if (!check_refname_format(o->local_ref, 0) &&
-		is_null_sha1(local_sha1))
-		local = NULL; /* local_sha1 == null_sha1 indicates unborn ref */
-	else if (!(local = lookup_commit_reference(local_sha1)))
+		is_null_oid(&local_oid))
+		local = NULL; /* local_oid == null_oid indicates unborn ref */
+	else if (!(local = lookup_commit_reference(&local_oid)))
 		die("Could not parse local commit %s (%s)",
-		    sha1_to_hex(local_sha1), o->local_ref);
-	trace_printf("\tlocal commit: %.7s\n", sha1_to_hex(local_sha1));
+		    oid_to_hex(&local_oid), o->local_ref);
+	trace_printf("\tlocal commit: %.7s\n", oid_to_hex(&local_oid));
 
-	/* Dereference o->remote_ref into remote_sha1 */
-	if (get_sha1(o->remote_ref, remote_sha1)) {
+	/* Dereference o->remote_ref into remote_oid */
+	if (get_oid(o->remote_ref, &remote_oid)) {
 		/*
-		 * Failed to get remote_sha1. If o->remote_ref looks like an
+		 * Failed to get remote_oid. If o->remote_ref looks like an
 		 * unborn ref, perform the merge using an empty notes tree.
 		 */
 		if (!check_refname_format(o->remote_ref, 0)) {
-			hashclr(remote_sha1);
+			oidclr(&remote_oid);
 			remote = NULL;
 		} else {
 			die("Failed to resolve remote notes ref '%s'",
 			    o->remote_ref);
 		}
-	} else if (!(remote = lookup_commit_reference(remote_sha1))) {
+	} else if (!(remote = lookup_commit_reference(&remote_oid))) {
 		die("Could not parse remote commit %s (%s)",
-		    sha1_to_hex(remote_sha1), o->remote_ref);
+		    oid_to_hex(&remote_oid), o->remote_ref);
 	}
-	trace_printf("\tremote commit: %.7s\n", sha1_to_hex(remote_sha1));
+	trace_printf("\tremote commit: %.7s\n", oid_to_hex(&remote_oid));
 
 	if (!local && !remote)
 		die("Cannot merge empty notes ref (%s) into empty notes ref "
 		    "(%s)", o->remote_ref, o->local_ref);
 	if (!local) {
 		/* result == remote commit */
-		hashcpy(result_sha1, remote_sha1);
+		oidcpy(result_oid, &remote_oid);
 		goto found_result;
 	}
 	if (!remote) {
 		/* result == local commit */
-		hashcpy(result_sha1, local_sha1);
+		oidcpy(result_oid, &local_oid);
 		goto found_result;
 	}
 	assert(local && remote);
 
 	/* Find merge bases */
 	bases = get_merge_bases(local, remote);
 	if (!bases) {
-		base_sha1 = null_sha1;
-		base_tree_sha1 = EMPTY_TREE_SHA1_BIN;
+		base_oid = &null_oid;
+		base_tree_oid = &empty_tree_oid;
 		if (o->verbosity >= 4)
 			printf("No merge base found; doing history-less merge\n");
 	} else if (!bases->next) {
-		base_sha1 = bases->item->object.oid.hash;
-		base_tree_sha1 = bases->item->tree->object.oid.hash;
+		base_oid = &bases->item->object.oid;
+		base_tree_oid = &bases->item->tree->object.oid;
 		if (o->verbosity >= 4)
 			printf("One merge base found (%.7s)\n",
-				sha1_to_hex(base_sha1));
+			       oid_to_hex(base_oid));
 	} else {
 		/* TODO: How to handle multiple merge-bases? */
-		base_sha1 = bases->item->object.oid.hash;
-		base_tree_sha1 = bases->item->tree->object.oid.hash;
+		base_oid = &bases->item->object.oid;
+		base_tree_oid = &bases->item->tree->object.oid;
 		if (o->verbosity >= 3)
 			printf("Multiple merge bases found. Using the first "
-				"(%.7s)\n", sha1_to_hex(base_sha1));
+				"(%.7s)\n", oid_to_hex(base_oid));
 	}
 
 	if (o->verbosity >= 4)
 		printf("Merging remote commit %.7s into local commit %.7s with "
 			"merge-base %.7s\n", oid_to_hex(&remote->object.oid),
 			oid_to_hex(&local->object.oid),
-			sha1_to_hex(base_sha1));
+			oid_to_hex(base_oid));
 
-	if (!hashcmp(remote->object.oid.hash, base_sha1)) {
+	if (!oidcmp(&remote->object.oid, base_oid)) {
 		/* Already merged; result == local commit */
 		if (o->verbosity >= 2)
 			printf("Already up-to-date!\n");
-		hashcpy(result_sha1, local->object.oid.hash);
+		oidcpy(result_oid, &local->object.oid);
 		goto found_result;
 	}
-	if (!hashcmp(local->object.oid.hash, base_sha1)) {
+	if (!oidcmp(&local->object.oid, base_oid)) {
 		/* Fast-forward; result == remote commit */
 		if (o->verbosity >= 2)
 			printf("Fast-forward\n");
-		hashcpy(result_sha1, remote->object.oid.hash);
+		oidcpy(result_oid, &remote->object.oid);
 		goto found_result;
 	}
 
-	result = merge_from_diffs(o, base_tree_sha1, local->tree->object.oid.hash,
-				  remote->tree->object.oid.hash, local_tree);
+	result = merge_from_diffs(o, base_tree_oid, &local->tree->object.oid,
+				  &remote->tree->object.oid, local_tree);
 
 	if (result != 0) { /* non-trivial merge (with or without conflicts) */
 		/* Commit (partial) result */
 		struct commit_list *parents = NULL;
 		commit_list_insert(remote, &parents); /* LIFO order */
 		commit_list_insert(local, &parents);
 		create_notes_commit(local_tree, parents,
 				    o->commit_msg.buf, o->commit_msg.len,
-				    result_sha1);
+				    result_oid->hash);
 	}
 
 found_result:
 	free_commit_list(bases);
 	strbuf_release(&(o->commit_msg));
-	trace_printf("notes_merge(): result = %i, result_sha1 = %.7s\n",
-	       result, sha1_to_hex(result_sha1));
+	trace_printf("notes_merge(): result = %i, result_oid = %.7s\n",
+	       result, oid_to_hex(result_oid));
 	return result;
 }
 
 int notes_merge_commit(struct notes_merge_options *o,
 		       struct notes_tree *partial_tree,
 		       struct commit *partial_commit,
-		       unsigned char *result_sha1)
+		       struct object_id *result_oid)
 {
 	/*
 	 * Iterate through files in .git/NOTES_MERGE_WORKTREE and add all
 	 * found notes to 'partial_tree'. Write the updated notes tree to
 	 * the DB, and commit the resulting tree object while reusing the
 	 * commit message and parents from 'partial_commit'.
-	 * Finally store the new commit object SHA1 into 'result_sha1'.
+	 * Finally store the new commit object OID into 'result_oid'.
 	 */
 	DIR *dir;
 	struct dirent *e;
 	struct strbuf path = STRBUF_INIT;
 	const char *buffer = get_commit_buffer(partial_commit, NULL);
 	const char *msg = strstr(buffer, "\n\n");
