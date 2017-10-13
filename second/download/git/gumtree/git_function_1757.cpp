static void execute_commands(struct command *commands,
			     const char *unpacker_error,
			     struct shallow_info *si)
{
	int checked_connectivity;
	struct command *cmd;
	unsigned char sha1[20];
	struct iterate_data data;

	if (unpacker_error) {
		for (cmd = commands; cmd; cmd = cmd->next)
			cmd->error_string = "unpacker error";
		return;
	}

	data.cmds = commands;
	data.si = si;
	if (check_everything_connected(iterate_receive_command_list, 0, &data))
		set_connectivity_errors(commands, si);

	reject_updates_to_hidden(commands);

	if (run_receive_hook(commands, "pre-receive", 0)) {
		for (cmd = commands; cmd; cmd = cmd->next) {
			if (!cmd->error_string)
				cmd->error_string = "pre-receive hook declined";
		}
		return;
	}

	check_aliased_updates(commands);

	free(head_name_to_free);
	head_name = head_name_to_free = resolve_refdup("HEAD", 0, sha1, NULL);

	checked_connectivity = 1;
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string)
			continue;

		if (cmd->skip_update)
			continue;

		cmd->error_string = update(cmd, si);
		if (shallow_update && !cmd->error_string &&
		    si->shallow_ref[cmd->index]) {
			error("BUG: connectivity check has not been run on ref %s",
			      cmd->ref_name);
			checked_connectivity = 0;
		}
	}

	if (shallow_update && !checked_connectivity)
		error("BUG: run 'git fsck' for safety.\n"
		      "If there are errors, try to remove "
		      "the reported refs above");
}