int capture_command(struct child_process *cmd, struct strbuf *buf, size_t hint)
{
	cmd->out = -1;
	if (start_command(cmd) < 0)
		return -1;

	if (strbuf_read(buf, cmd->out, hint) < 0) {
		close(cmd->out);
		finish_command(cmd); /* throw away exit code */
		return -1;
	}

	close(cmd->out);
	return finish_command(cmd);
}