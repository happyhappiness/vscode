int submodule_uses_gitfile(const char *path)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *argv[] = {
		"submodule",
		"foreach",
		"--quiet",
		"--recursive",
		"test -f .git",
		NULL,
	};
	struct strbuf buf = STRBUF_INIT;
	const char *git_dir;

	strbuf_addf(&buf, "%s/.git", path);
	git_dir = read_gitfile(buf.buf);
	if (!git_dir) {
		strbuf_release(&buf);
		return 0;
	}
	strbuf_release(&buf);

	/* Now test that all nested submodules use a gitfile too */
	cp.argv = argv;
	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.no_stderr = 1;
	cp.no_stdout = 1;
	cp.dir = path;
	if (run_command(&cp))
		return 0;

	return 1;
}