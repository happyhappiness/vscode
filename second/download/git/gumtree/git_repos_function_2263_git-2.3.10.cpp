static int read_from_command(struct child_process *cp, struct strbuf *buf)
{
	if (run_command(cp))
		return error("running trailer command '%s' failed", cp->argv[0]);
	if (strbuf_read(buf, cp->out, 1024) < 1)
		return error("reading from trailer command '%s' failed", cp->argv[0]);
	strbuf_trim(buf);
	return 0;
}