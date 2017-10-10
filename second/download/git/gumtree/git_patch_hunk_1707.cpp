 	struct merge_parents merge_parents;
 
 	memset(&merge_parents, 0, sizeof(merge_parents));
 
 	/* get current branch */
 	current_branch = current_branch_to_free =
-		resolve_refdup("HEAD", head_sha1, 1, NULL);
+		resolve_refdup("HEAD", RESOLVE_REF_READING, head_sha1, NULL);
 	if (!current_branch)
 		die("No current branch");
 	if (starts_with(current_branch, "refs/heads/"))
 		current_branch += 11;
 
 	find_merge_parents(&merge_parents, in, head_sha1);
