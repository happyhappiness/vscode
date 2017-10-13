int ok_to_remove_submodule(const char *path)
{
	ssize_t len;
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *argv[] = {
		"status",
		"--porcelain",
		"-u",
		"--ignore-submodules=none",
		NULL,
	};
	struct strbuf buf = STRBUF_INIT;
	int ok_to_remove = 1;

	if (!file_exists(path) || is_empty_dir(path))
		return 1;

	if (!submodule_uses_gitfile(path))
		return 0;

	cp.argv = argv;
	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp))
		die("Could not run 'git status --porcelain -uall --ignore-submodules=none' in submodule %s", path);

	len = strbuf_read(&buf, cp.out, 1024);
	if (len > 2)
		ok_to_remove = 0;
	close(cp.out);

	if (finish_command(&cp))
		die("'git status --porcelain -uall --ignore-submodules=none' failed in submodule %s", path);

	strbuf_release(&buf);
	return ok_to_remove;
}