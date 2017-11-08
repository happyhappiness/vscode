static int delete_only(struct command *commands)
{
	struct command *cmd;
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!is_null_oid(&cmd->new_oid))
			return 0;
	}
	return 1;
}