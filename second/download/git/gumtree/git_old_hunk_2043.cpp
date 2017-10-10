			cmd->error_string = "deny deleting a hidden ref";
		else
			cmd->error_string = "deny updating a hidden ref";
	}
}

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
