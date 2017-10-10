 		const char *argv[] = {"rev-list", NULL, "--not", "--remotes", "-n", "1" , NULL};
 		struct strbuf buf = STRBUF_INIT;
 		int needs_pushing = 0;
 
 		argv[1] = sha1_to_hex(sha1);
 		cp.argv = argv;
-		cp.env = local_repo_env;
+		prepare_submodule_repo_env(&cp.env_array);
 		cp.git_cmd = 1;
 		cp.no_stdin = 1;
 		cp.out = -1;
 		cp.dir = path;
 		if (start_command(&cp))
 			die("Could not run 'git rev-list %s --not --remotes -n 1' command in submodule %s",
