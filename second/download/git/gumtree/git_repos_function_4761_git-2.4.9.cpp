static int delete_only(struct command *commands)
{
	struct command *cmd;
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!is_null_sha1(cmd->new_sha1))
			return 0;
	}
	return 1;
}