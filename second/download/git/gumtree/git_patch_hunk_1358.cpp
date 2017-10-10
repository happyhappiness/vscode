 		OPT_SET_INT(0, "hard", &reset_type,
 				N_("reset HEAD, index and working tree"), HARD),
 		OPT_SET_INT(0, "merge", &reset_type,
 				N_("reset HEAD, index and working tree"), MERGE),
 		OPT_SET_INT(0, "keep", &reset_type,
 				N_("reset HEAD but keep local changes"), KEEP),
+		{ OPTION_CALLBACK, 0, "recurse-submodules", NULL,
+			    "reset", "control recursive updating of submodules",
+			    PARSE_OPT_OPTARG, option_parse_recurse_submodules_worktree_updater },
 		OPT_BOOL('p', "patch", &patch_mode, N_("select hunks interactively")),
 		OPT_BOOL('N', "intent-to-add", &intent_to_add,
 				N_("record only the fact that removed paths will be added later")),
 		OPT_END()
 	};
 
-	git_config(git_default_config, NULL);
+	git_config(git_reset_config, NULL);
 
 	argc = parse_options(argc, argv, prefix, options, git_reset_usage,
 						PARSE_OPT_KEEP_DASHDASH);
 	parse_args(&pathspec, argv, prefix, patch_mode, &rev);
 
+	load_submodule_cache();
+
 	unborn = !strcmp(rev, "HEAD") && get_sha1("HEAD", oid.hash);
 	if (unborn) {
 		/* reset on unborn branch: treat as reset to empty tree */
 		hashcpy(oid.hash, EMPTY_TREE_SHA1_BIN);
 	} else if (!pathspec.nr) {
 		struct commit *commit;
 		if (get_sha1_committish(rev, oid.hash))
 			die(_("Failed to resolve '%s' as a valid revision."), rev);
-		commit = lookup_commit_reference(oid.hash);
+		commit = lookup_commit_reference(&oid);
 		if (!commit)
 			die(_("Could not parse object '%s'."), rev);
 		oidcpy(&oid, &commit->object.oid);
 	} else {
 		struct tree *tree;
 		if (get_sha1_treeish(rev, oid.hash))
 			die(_("Failed to resolve '%s' as a valid tree."), rev);
-		tree = parse_tree_indirect(oid.hash);
+		tree = parse_tree_indirect(&oid);
 		if (!tree)
 			die(_("Could not parse object '%s'."), rev);
 		oidcpy(&oid, &tree->object.oid);
 	}
 
 	if (patch_mode) {
