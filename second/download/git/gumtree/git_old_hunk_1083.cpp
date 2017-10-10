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
