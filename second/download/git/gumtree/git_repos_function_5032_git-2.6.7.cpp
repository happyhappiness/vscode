static int should_process_cmd(struct command *cmd)
{
	return !cmd->error_string && !cmd->skip_update;
}