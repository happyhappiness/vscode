 * author metadata.
 */
static int run_git_commit(const char *defmsg, struct replay_opts *opts,
			  int allow_empty, int edit, int amend,
			  int cleanup_commit_message)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	const char *value;

	cmd.git_cmd = 1;

	if (is_rebase_i(opts)) {
		if (!edit) {
			cmd.stdout_to_stderr = 1;
			cmd.err = -1;
		}

		if (read_env_script(&cmd.env_array)) {
			const char *gpg_opt = gpg_sign_opt_quoted(opts);

			return error(_(staged_changes_advice),
				     gpg_opt, gpg_opt);
		}
	}

	argv_array_push(&cmd.args, "commit");
	argv_array_push(&cmd.args, "-n");

	if (amend)
		argv_array_push(&cmd.args, "--amend");
	if (opts->gpg_sign)
		argv_array_pushf(&cmd.args, "-S%s", opts->gpg_sign);
	if (opts->signoff)
		argv_array_push(&cmd.args, "-s");
	if (defmsg)
		argv_array_pushl(&cmd.args, "-F", defmsg, NULL);
	if (cleanup_commit_message)
		argv_array_push(&cmd.args, "--cleanup=strip");
	if (edit)
		argv_array_push(&cmd.args, "-e");
	else if (!cleanup_commit_message &&
		 !opts->signoff && !opts->record_origin &&
		 git_config_get_value("commit.cleanup", &value))
		argv_array_push(&cmd.args, "--cleanup=verbatim");

	if (allow_empty)
		argv_array_push(&cmd.args, "--allow-empty");

	if (opts->allow_empty_message)
		argv_array_push(&cmd.args, "--allow-empty-message");

	if (cmd.err == -1) {
		/* hide stderr on success */
		struct strbuf buf = STRBUF_INIT;
		int rc = pipe_command(&cmd,
				      NULL, 0,
				      /* stdout is already redirected */
				      NULL, 0,
				      &buf, 0);
		if (rc)
			fputs(buf.buf, stderr);
		strbuf_release(&buf);
		return rc;
	}

	return run_command(&cmd);
}

static int is_original_commit_empty(struct commit *commit)
{
	const unsigned char *ptree_sha1;

