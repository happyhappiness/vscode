static int is_submodule_commit_present(const char *path, unsigned char sha1[20])
{
	int is_present = 0;
	if (!add_submodule_odb(path) && lookup_commit_reference(sha1)) {
		/* Even if the submodule is checked out and the commit is
		 * present, make sure it is reachable from a ref. */
		struct child_process cp;
		const char *argv[] = {"rev-list", "-n", "1", NULL, "--not", "--all", NULL};
		struct strbuf buf = STRBUF_INIT;

		argv[3] = sha1_to_hex(sha1);
		memset(&cp, 0, sizeof(cp));
		cp.argv = argv;
		cp.env = local_repo_env;
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.out = -1;
		cp.dir = path;
		if (!run_command(&cp) && !strbuf_read(&buf, cp.out, 1024))
			is_present = 1;

		close(cp.out);
		strbuf_release(&buf);
	}
	return is_present;
}