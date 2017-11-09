static inline int capture_command(struct child_process *cmd,
				  struct strbuf *out,
				  size_t hint)
{
	return pipe_command(cmd, NULL, 0, out, hint, NULL, 0);
}