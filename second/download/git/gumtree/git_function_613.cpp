static int run_git_commit(const char *defmsg, struct replay_opts *opts,
			  int allow_empty, int edit, int amend,
			  int cleanup_commit_message)
{
	char **env = NULL;
	struct argv_array array;
	int rc;
	const char *value;

	if (is_rebase_i(opts)) {
		env = read_author_script();
		if (!env) {
			const char *gpg_opt = gpg_sign_opt_quoted(opts);

			return error(_(staged_changes_advice),
				     gpg_opt, gpg_opt);
		}
	}

	argv_array_init(&array);
	argv_array_push(&array, "commit");
	argv_array_push(&array, "-n");

	if (amend)
		argv_array_push(&array, "--amend");
	if (opts->gpg_sign)
		argv_array_pushf(&array, "-S%s", opts->gpg_sign);
	if (opts->signoff)
		argv_array_push(&array, "-s");
	if (defmsg)
		argv_array_pushl(&array, "-F", defmsg, NULL);
	if (cleanup_commit_message)
		argv_array_push(&array, "--cleanup=strip");
	if (edit)
		argv_array_push(&array, "-e");
	else if (!cleanup_commit_message &&
		 !opts->signoff && !opts->record_origin &&
		 git_config_get_value("commit.cleanup", &value))
		argv_array_push(&array, "--cleanup=verbatim");

	if (allow_empty)
		argv_array_push(&array, "--allow-empty");

	if (opts->allow_empty_message)
		argv_array_push(&array, "--allow-empty-message");

	rc = run_command_v_opt_cd_env(array.argv, RUN_GIT_CMD, NULL,
			(const char *const *)env);
	argv_array_clear(&array);
	free(env);

	return rc;
}