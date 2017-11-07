int run_command(struct child_process *cmd)
{
	int code;

	if (cmd->out < 0 || cmd->err < 0)
		die("BUG: run_command with a pipe can cause deadlock");

	code = start_command(cmd);
	if (code)
		return code;
	return finish_command(cmd);
}