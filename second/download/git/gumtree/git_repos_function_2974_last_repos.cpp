static int run_git_commit(const char *defmsg, struct replay_opts *opts,
			  unsigned int flags)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	const char *value;

	cmd.git_cmd = 1;

	if (is_rebase_i(opts)) {
		if (!(flags & EDIT_MSG)) {
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

	if (!(flags & VERIFY_MSG))
		argv_array_push(&cmd.args, "-n");
	if ((flags & AMEND_MSG))
		argv_array_push(&cmd.args, "--amend");
	if (opts->gpg_sign)
		argv_array_pushf(&cmd.args, "-S%s", opts->gpg_sign);
	if (opts->signoff)
		argv_array_push(&cmd.args, "-s");
	if (defmsg)
		argv_array_pushl(&cmd.args, "-F", defmsg, NULL);
	if ((flags & CLEANUP_MSG))
		argv_array_push(&cmd.args, "--cleanup=strip");
	if ((flags & EDIT_MSG))
		argv_array_push(&cmd.args, "-e");
	else if (!(flags & CLEANUP_MSG) &&
		 !opts->signoff && !opts->record_origin &&
		 git_config_get_value("commit.cleanup", &value))
		argv_array_push(&cmd.args, "--cleanup=verbatim");

	if ((flags & ALLOW_EMPTY))
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