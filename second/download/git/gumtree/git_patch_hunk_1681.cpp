 
 	/* --track without -b/-B/--orphan should DWIM */
 	if (opts.track != BRANCH_TRACK_UNSPECIFIED && !opts.new_branch) {
 		const char *argv0 = argv[0];
 		if (!argc || !strcmp(argv0, "--"))
 			die (_("--track needs a branch name"));
-		if (starts_with(argv0, "refs/"))
-			argv0 += 5;
-		if (starts_with(argv0, "remotes/"))
-			argv0 += 8;
+		skip_prefix(argv0, "refs/", &argv0);
+		skip_prefix(argv0, "remotes/", &argv0);
 		argv0 = strchr(argv0, '/');
 		if (!argv0 || !argv0[1])
 			die (_("Missing branch name; try -b"));
 		opts.new_branch = argv0 + 1;
 	}
 
