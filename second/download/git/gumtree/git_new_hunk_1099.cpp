		find_unpushed_submodule_commits(commit, &submodules);

	reset_revision_walk();
	argv_array_clear(&argv);

	for_each_string_list_item(submodule, &submodules) {
		struct oid_array *commits = (struct oid_array *) submodule->util;

		if (submodule_needs_pushing(submodule->string, commits))
			string_list_insert(needs_pushing, submodule->string);
	}
	free_submodules_sha1s(&submodules);

	return needs_pushing->nr;
}

static int push_submodule(const char *path,
			  const struct remote *remote,
			  const char **refspec, int refspec_nr,
			  const struct string_list *push_options,
			  int dry_run)
{
	if (add_submodule_odb(path))
		return 1;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		argv_array_push(&cp.args, "push");
		if (dry_run)
			argv_array_push(&cp.args, "--dry-run");

		if (push_options && push_options->nr) {
			const struct string_list_item *item;
			for_each_string_list_item(item, push_options)
				argv_array_pushf(&cp.args, "--push-option=%s",
						 item->string);
		}

		if (remote->origin != REMOTE_UNCONFIGURED) {
			int i;
			argv_array_push(&cp.args, remote->name);
			for (i = 0; i < refspec_nr; i++)
				argv_array_push(&cp.args, refspec[i]);
		}

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

/*
 * Perform a check in the submodule to see if the remote and refspec work.
 * Die if the submodule can't be pushed.
 */
static void submodule_push_check(const char *path, const struct remote *remote,
				 const char **refspec, int refspec_nr)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int i;

	argv_array_push(&cp.args, "submodule--helper");
	argv_array_push(&cp.args, "push-check");
	argv_array_push(&cp.args, remote->name);

	for (i = 0; i < refspec_nr; i++)
		argv_array_push(&cp.args, refspec[i]);

	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.no_stdout = 1;
	cp.dir = path;

	/*
	 * Simply indicate if 'submodule--helper push-check' failed.
	 * More detailed error information will be provided by the
	 * child process.
	 */
	if (run_command(&cp))
		die("process for submodule '%s' failed", path);
}

int push_unpushed_submodules(struct oid_array *commits,
			     const struct remote *remote,
			     const char **refspec, int refspec_nr,
			     const struct string_list *push_options,
			     int dry_run)
{
	int i, ret = 1;
	struct string_list needs_pushing = STRING_LIST_INIT_DUP;

	if (!find_unpushed_submodules(commits, remote->name, &needs_pushing))
		return 1;

	/*
	 * Verify that the remote and refspec can be propagated to all
	 * submodules.  This check can be skipped if the remote and refspec
	 * won't be propagated due to the remote being unconfigured (e.g. a URL
	 * instead of a remote name).
	 */
	if (remote->origin != REMOTE_UNCONFIGURED)
		for (i = 0; i < needs_pushing.nr; i++)
			submodule_push_check(needs_pushing.items[i].string,
					     remote, refspec, refspec_nr);

	/* Actually push the submodules */
	for (i = 0; i < needs_pushing.nr; i++) {
		const char *path = needs_pushing.items[i].string;
		fprintf(stderr, "Pushing submodule '%s'\n", path);
		if (!push_submodule(path, remote, refspec, refspec_nr,
				    push_options, dry_run)) {
			fprintf(stderr, "Unable to push submodule '%s'\n", path);
			ret = 0;
		}
	}

	string_list_clear(&needs_pushing, 0);
