		return 1;

	if (!submodule_uses_gitfile(path))
		return 0;

	cp.argv = argv;
	cp.env = local_repo_env;
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp))
		die("Could not run 'git status --porcelain -uall --ignore-submodules=none' in submodule %s", path);
