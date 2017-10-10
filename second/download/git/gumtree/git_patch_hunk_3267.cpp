 		if (!strcmp(argv[i], "--")) {
 			has_dashdash = 1;
 			break;
 		}
 	}
 
-	prefix = setup_git_directory();
-	git_config(git_default_config, NULL);
+	/* No options; just report on whether we're in a git repo or not. */
+	if (argc == 1) {
+		setup_git_directory();
+		git_config(git_default_config, NULL);
+		return 0;
+	}
+
 	for (i = 1; i < argc; i++) {
 		const char *arg = argv[i];
 
+		if (!strcmp(arg, "--local-env-vars")) {
+			int i;
+			for (i = 0; local_repo_env[i]; i++)
+				printf("%s\n", local_repo_env[i]);
+			continue;
+		}
+		if (!strcmp(arg, "--resolve-git-dir")) {
+			const char *gitdir = argv[++i];
+			if (!gitdir)
+				die("--resolve-git-dir requires an argument");
+			gitdir = resolve_gitdir(gitdir);
+			if (!gitdir)
+				die("not a gitdir '%s'", argv[i]);
+			puts(gitdir);
+			continue;
+		}
+
+		/* The rest of the options require a git repository. */
+		if (!did_repo_setup) {
+			prefix = setup_git_directory();
+			git_config(git_default_config, NULL);
+			did_repo_setup = 1;
+		}
+
 		if (!strcmp(arg, "--git-path")) {
 			if (!argv[i + 1])
 				die("--git-path requires an argument");
 			puts(git_path("%s", argv[i + 1]));
 			i++;
 			continue;
