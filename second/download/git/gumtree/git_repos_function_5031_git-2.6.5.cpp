static void reject_updates_to_hidden(struct command *commands)
{
	struct command *cmd;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string || !ref_is_hidden(cmd->ref_name))
			continue;
		if (is_null_sha1(cmd->new_sha1))
			cmd->error_string = "deny deleting a hidden ref";
		else
			cmd->error_string = "deny updating a hidden ref";
	}
}