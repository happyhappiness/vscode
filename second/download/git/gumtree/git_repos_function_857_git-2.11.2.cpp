int finish_command(struct child_process *cmd)
{
	int ret = wait_or_whine(cmd->pid, cmd->argv[0], 0);
	child_process_clear(cmd);
	return ret;
}