static int run_git_commit(const char *defmsg, struct replay_opts *opts,
			  int allow_empty)
{
	struct argv_array array;
	int rc;
	const char *value;

	argv_array_init(&array);
	argv_array_push(&array, "commit");
	argv_array_push(&array, "-n");

	if (opts->gpg_sign)
		argv_array_pushf(&array, "-S%s", opts->gpg_sign);
	if (opts->signoff)
		argv_array_push(&array, "-s");
	if (!opts->edit) {
		argv_array_push(&array, "-F");
		argv_array_push(&array, defmsg);
		if (!opts->signoff &&
		    !opts->record_origin &&
		    git_config_get_value("commit.cleanup", &value))
			argv_array_push(&array, "--cleanup=verbatim");
	}

	if (allow_empty)
		argv_array_push(&array, "--allow-empty");

	if (opts->allow_empty_message)
		argv_array_push(&array, "--allow-empty-message");

	rc = run_command_v_opt(array.argv, RUN_GIT_CMD);
	argv_array_clear(&array);
	return rc;
}