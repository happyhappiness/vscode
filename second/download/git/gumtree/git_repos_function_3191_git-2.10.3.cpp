static int is_submodule_commit_present(const char *path, unsigned char sha1[20])
{
	int is_present = 0;
	if (!add_submodule_odb(path) && lookup_commit_reference(sha1)) {
		/* Even if the submodule is checked out and the commit is
		 * present, make sure it is reachable from a ref. */
		struct child_process cp = CHILD_PROCESS_INIT;
		const char *argv[] = {"rev-list", "-n", "1", NULL, "--not", "--all", NULL};
		struct strbuf buf = STRBUF_INIT;

		argv[3] = sha1_to_hex(sha1);
		cp.argv = argv;
		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.dir = path;
		if (!capture_command(&cp, &buf, 1024) && !buf.len)
			is_present = 1;

		strbuf_release(&buf);
	}
	return is_present;
}