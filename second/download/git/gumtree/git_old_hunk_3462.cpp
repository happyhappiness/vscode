	strbuf_reset(&buf);

	if (ignore_untracked)
		argv[2] = "-uno";

	cp.argv = argv;
	cp.env = local_repo_env;
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp))
		die("Could not run 'git status --porcelain' in submodule %s", path);
