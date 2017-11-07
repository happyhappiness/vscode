int finish_command(struct child_process *cmd)
{
	return wait_or_whine(cmd->pid, cmd->argv[0]);
}