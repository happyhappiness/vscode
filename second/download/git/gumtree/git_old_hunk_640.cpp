	rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = collect_submodules_from_diff;
	rev.diffopt.format_callback_data = needs_pushing;
	diff_tree_combined_merge(commit, 1, &rev);
}

int find_unpushed_submodules(unsigned char new_sha1[20],
		const char *remotes_name, struct string_list *needs_pushing)
{
	struct rev_info rev;
	struct commit *commit;
	const char *argv[] = {NULL, NULL, "--not", "NULL", NULL};
	int argc = ARRAY_SIZE(argv) - 1;
	char *sha1_copy;

	struct strbuf remotes_arg = STRBUF_INIT;

	strbuf_addf(&remotes_arg, "--remotes=%s", remotes_name);
	init_revisions(&rev, NULL);
	sha1_copy = xstrdup(sha1_to_hex(new_sha1));
	argv[1] = sha1_copy;
	argv[3] = remotes_arg.buf;
	setup_revisions(argc, argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	while ((commit = get_revision(&rev)) != NULL)
		find_unpushed_submodule_commits(commit, needs_pushing);

	reset_revision_walk();
	free(sha1_copy);
	strbuf_release(&remotes_arg);

	return needs_pushing->nr;
}

static int push_submodule(const char *path)
{
	if (add_submodule_odb(path))
		return 1;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		const char *argv[] = {"push", NULL};

		cp.argv = argv;
		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.dir = path;
		if (run_command(&cp))
			return 0;
		close(cp.out);
	}

	return 1;
}

int push_unpushed_submodules(unsigned char new_sha1[20], const char *remotes_name)
{
	int i, ret = 1;
	struct string_list needs_pushing = STRING_LIST_INIT_DUP;

	if (!find_unpushed_submodules(new_sha1, remotes_name, &needs_pushing))
		return 1;

	for (i = 0; i < needs_pushing.nr; i++) {
		const char *path = needs_pushing.items[i].string;
		fprintf(stderr, "Pushing submodule '%s'\n", path);
		if (!push_submodule(path)) {
			fprintf(stderr, "Unable to push submodule '%s'\n", path);
			ret = 0;
		}
	}

	string_list_clear(&needs_pushing, 0);
