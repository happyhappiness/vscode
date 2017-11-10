static int run_git_commit(const char *defmsg, struct replay_opts *opts,
			  int allow_empty)
{
	struct argv_array array;
	int rc;
	char *gpg_sign;

	argv_array_init(&array);
	argv_array_push(&array, "commit");
	argv_array_push(&array, "-n");

	if (opts->gpg_sign) {
		gpg_sign = xmalloc(3 + strlen(opts->gpg_sign));
		sprintf(gpg_sign, "-S%s", opts->gpg_sign);
		argv_array_push(&array, gpg_sign);
		free(gpg_sign);
	}
	if (opts->signoff)
		argv_array_push(&array, "-s");
	if (!opts->edit) {
		argv_array_push(&array, "-F");
		argv_array_push(&array, defmsg);
	}

	if (allow_empty)
		argv_array_push(&array, "--allow-empty");

	if (opts->allow_empty_message)
		argv_array_push(&array, "--allow-empty-message");

	rc = run_command_v_opt(array.argv, RUN_GIT_CMD);
	argv_array_clear(&array);
	return rc;
}