static void execute_commands(struct command *commands,
			     const char *unpacker_error,
			     struct shallow_info *si,
			     const struct string_list *push_options)
{
	struct check_connected_options opt = CHECK_CONNECTED_INIT;
	struct command *cmd;
	unsigned char sha1[20];
	struct iterate_data data;
	struct async muxer;
	int err_fd = 0;

	if (unpacker_error) {
		for (cmd = commands; cmd; cmd = cmd->next)
			cmd->error_string = "unpacker error";
		return;
	}

	if (use_sideband) {
		memset(&muxer, 0, sizeof(muxer));
		muxer.proc = copy_to_sideband;
		muxer.in = -1;
		if (!start_async(&muxer))
			err_fd = muxer.in;
		/* ...else, continue without relaying sideband */
	}

	data.cmds = commands;
	data.si = si;
	opt.err_fd = err_fd;
	opt.progress = err_fd && !quiet;
	opt.env = tmp_objdir_env(tmp_objdir);
	if (check_connected(iterate_receive_command_list, &data, &opt))
		set_connectivity_errors(commands, si);

	if (use_sideband)
		finish_async(&muxer);

	reject_updates_to_hidden(commands);

	if (run_receive_hook(commands, "pre-receive", 0, push_options)) {
		for (cmd = commands; cmd; cmd = cmd->next) {
			if (!cmd->error_string)
				cmd->error_string = "pre-receive hook declined";
		}
		return;
	}

	/*
	 * Now we'll start writing out refs, which means the objects need
	 * to be in their final positions so that other processes can see them.
	 */
	if (tmp_objdir_migrate(tmp_objdir) < 0) {
		for (cmd = commands; cmd; cmd = cmd->next) {
			if (!cmd->error_string)
				cmd->error_string = "unable to migrate objects to permanent storage";
		}
		return;
	}
	tmp_objdir = NULL;

	check_aliased_updates(commands);

	free(head_name_to_free);
	head_name = head_name_to_free = resolve_refdup("HEAD", 0, sha1, NULL);

	if (use_atomic)
		execute_commands_atomic(commands, si);
	else
		execute_commands_non_atomic(commands, si);

	if (shallow_update)
		warn_if_skipped_connectivity_check(commands, si);
}