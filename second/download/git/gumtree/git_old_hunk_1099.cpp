		find_unpushed_submodule_commits(commit, &submodules);

	reset_revision_walk();
	argv_array_clear(&argv);

	for_each_string_list_item(submodule, &submodules) {
		struct sha1_array *commits = (struct sha1_array *) submodule->util;

		if (submodule_needs_pushing(submodule->string, commits))
			string_list_insert(needs_pushing, submodule->string);
	}
	free_submodules_sha1s(&submodules);

	return needs_pushing->nr;
}

static int push_submodule(const char *path, int dry_run)
{
	if (add_submodule_odb(path))
		return 1;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		argv_array_push(&cp.args, "push");
		if (dry_run)
			argv_array_push(&cp.args, "--dry-run");

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

int push_unpushed_submodules(struct sha1_array *commits,
			     const char *remotes_name,
			     int dry_run)
{
	int i, ret = 1;
	struct string_list needs_pushing = STRING_LIST_INIT_DUP;

	if (!find_unpushed_submodules(commits, remotes_name, &needs_pushing))
		return 1;

	for (i = 0; i < needs_pushing.nr; i++) {
		const char *path = needs_pushing.items[i].string;
		fprintf(stderr, "Pushing submodule '%s'\n", path);
		if (!push_submodule(path, dry_run)) {
			fprintf(stderr, "Unable to push submodule '%s'\n", path);
			ret = 0;
		}
	}

	string_list_clear(&needs_pushing, 0);
