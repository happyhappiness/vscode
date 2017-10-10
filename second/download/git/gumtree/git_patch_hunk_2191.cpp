 {
 	const char *name = argv[0];
 	const unsigned char *commit_sha1;
 	time_t archive_time;
 	struct tree *tree;
 	const struct commit *commit;
-	unsigned char sha1[20];
+	struct object_id oid;
 
 	/* Remotes are only allowed to fetch actual refs */
 	if (remote && !remote_allow_unreachable) {
 		char *ref = NULL;
 		const char *colon = strchrnul(name, ':');
 		int refnamelen = colon - name;
 
-		if (!dwim_ref(name, refnamelen, sha1, &ref))
+		if (!dwim_ref(name, refnamelen, oid.hash, &ref))
 			die("no such ref: %.*s", refnamelen, name);
 		free(ref);
 	}
 
-	if (get_sha1(name, sha1))
+	if (get_sha1(name, oid.hash))
 		die("Not a valid object name");
 
-	commit = lookup_commit_reference_gently(sha1, 1);
+	commit = lookup_commit_reference_gently(oid.hash, 1);
 	if (commit) {
 		commit_sha1 = commit->object.sha1;
 		archive_time = commit->date;
 	} else {
 		commit_sha1 = NULL;
 		archive_time = time(NULL);
 	}
 
-	tree = parse_tree_indirect(sha1);
+	tree = parse_tree_indirect(oid.hash);
 	if (tree == NULL)
 		die("not a tree object");
 
 	if (prefix) {
-		unsigned char tree_sha1[20];
+		struct object_id tree_oid;
 		unsigned int mode;
 		int err;
 
 		err = get_tree_entry(tree->object.sha1, prefix,
-				     tree_sha1, &mode);
+				     tree_oid.hash, &mode);
 		if (err || !S_ISDIR(mode))
 			die("current working directory is untracked");
 
-		tree = parse_tree_indirect(tree_sha1);
+		tree = parse_tree_indirect(tree_oid.hash);
 	}
 	ar_args->tree = tree;
 	ar_args->commit_sha1 = commit_sha1;
 	ar_args->commit = commit;
 	ar_args->time = archive_time;
 }
