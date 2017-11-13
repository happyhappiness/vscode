unsigned is_submodule_modified(const char *path, int ignore_untracked)
{
	ssize_t len;
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *argv[] = {
		"status",
		"--porcelain",
		NULL,
		NULL,
	};
	struct strbuf buf = STRBUF_INIT;
	unsigned dirty_submodule = 0;
	const char *line, *next_line;
	const char *git_dir;

	strbuf_addf(&buf, "%s/.git", path);
	git_dir = read_gitfile(buf.buf);
	if (!git_dir)
		git_dir = buf.buf;
	if (!is_directory(git_dir)) {
		strbuf_release(&buf);
		/* The submodule is not checked out, so it is not modified */
		return 0;

	}
	strbuf_reset(&buf);

	if (ignore_untracked)
		argv[2] = "-uno";

	cp.argv = argv;
	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp))
		die("Could not run 'git status --porcelain' in submodule %s", path);

	len = strbuf_read(&buf, cp.out, 1024);
	line = buf.buf;
	while (len > 2) {
		if ((line[0] == '?') && (line[1] == '?')) {
			dirty_submodule |= DIRTY_SUBMODULE_UNTRACKED;
			if (dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
				break;
		} else {
			dirty_submodule |= DIRTY_SUBMODULE_MODIFIED;
			if (ignore_untracked ||
			    (dirty_submodule & DIRTY_SUBMODULE_UNTRACKED))
				break;
		}
		next_line = strchr(line, '\n');
		if (!next_line)
			break;
		next_line++;
		len -= (next_line - line);
		line = next_line;
	}
	close(cp.out);

	if (finish_command(&cp))
		die("'git status --porcelain' failed in submodule %s", path);

	strbuf_release(&buf);
	return dirty_submodule;
}