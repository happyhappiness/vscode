static int submodule_needs_pushing(const char *path, const unsigned char sha1[20])
{
	if (add_submodule_odb(path) || !lookup_commit_reference(sha1))
		return 0;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		const char *argv[] = {"rev-list", NULL, "--not", "--remotes", "-n", "1" , NULL};
		struct strbuf buf = STRBUF_INIT;
		int needs_pushing = 0;

		argv[1] = sha1_to_hex(sha1);
		cp.argv = argv;
		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.out = -1;
		cp.dir = path;
		if (start_command(&cp))
			die("Could not run 'git rev-list %s --not --remotes -n 1' command in submodule %s",
				sha1_to_hex(sha1), path);
		if (strbuf_read(&buf, cp.out, 41))
			needs_pushing = 1;
		finish_command(&cp);
		close(cp.out);
		strbuf_release(&buf);
		return needs_pushing;
	}

	return 0;
}