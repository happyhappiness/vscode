
	return 0;
}

int finish_command(struct child_process *cmd)
{
	int ret = wait_or_whine(cmd->pid, cmd->argv[0]);
	argv_array_clear(&cmd->args);
	argv_array_clear(&cmd->env_array);
	return ret;
}

int run_command(struct child_process *cmd)
{
	int code;

	if (cmd->out < 0 || cmd->err < 0)
		die("BUG: run_command with a pipe can cause deadlock");
