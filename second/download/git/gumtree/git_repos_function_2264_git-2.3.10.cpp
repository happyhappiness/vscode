static const char *apply_command(const char *command, const char *arg)
{
	struct strbuf cmd = STRBUF_INIT;
	struct strbuf buf = STRBUF_INIT;
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *argv[] = {NULL, NULL};
	const char *result;

	strbuf_addstr(&cmd, command);
	if (arg)
		strbuf_replace(&cmd, TRAILER_ARG_STRING, arg);

	argv[0] = cmd.buf;
	cp.argv = argv;
	cp.env = local_repo_env;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.use_shell = 1;

	if (read_from_command(&cp, &buf)) {
		strbuf_release(&buf);
		result = xstrdup("");
	} else
		result = strbuf_detach(&buf, NULL);

	strbuf_release(&cmd);
	return result;
}