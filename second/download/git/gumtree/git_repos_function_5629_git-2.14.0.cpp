static int iterate_receive_command_list(void *cb_data, unsigned char sha1[20])
{
	struct iterate_data *data = cb_data;
	struct command **cmd_list = &data->cmds;
	struct command *cmd = *cmd_list;

	for (; cmd; cmd = cmd->next) {
		if (shallow_update && data->si->shallow_ref[cmd->index])
			/* to be checked in update_shallow_ref() */
			continue;
		if (!is_null_oid(&cmd->new_oid) && !cmd->skip_update) {
			hashcpy(sha1, cmd->new_oid.hash);
			*cmd_list = cmd->next;
			return 0;
		}
	}
	*cmd_list = NULL;
	return -1; /* end of list */
}