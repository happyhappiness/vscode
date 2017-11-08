int finish_command_in_signal(struct child_process *cmd)
{
	return wait_or_whine(cmd->pid, cmd->argv[0], 1);
}