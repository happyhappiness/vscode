static void execute_commands(struct command *commands,
			     const char *unpacker_error,
			     struct shallow_info *si)
{
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

	if (use_atomic)
		execute_commands_atomic(commands, si);
	else
		execute_commands_non_atomic(commands, si);

	if (shallow_update)
		warn_if_skipped_connectivity_check(commands, si);
}