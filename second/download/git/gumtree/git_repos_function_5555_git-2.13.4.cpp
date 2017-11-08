static int command_singleton_iterator(void *cb_data, unsigned char sha1[20])
{
	struct command **cmd_list = cb_data;
	struct command *cmd = *cmd_list;

	if (!cmd || is_null_oid(&cmd->new_oid))
		return -1; /* end of list */
	*cmd_list = NULL; /* this returns only one */
	hashcpy(sha1, cmd->new_oid.hash);
	return 0;
}