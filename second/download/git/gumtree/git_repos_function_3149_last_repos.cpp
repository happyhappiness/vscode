static int filter_buffer_or_fd(int in, int out, void *data)
{
	/*
	 * Spawn cmd and feed the buffer contents through its stdin.
	 */
	struct child_process child_process = CHILD_PROCESS_INIT;
	struct filter_params *params = (struct filter_params *)data;
	int write_err, status;
	const char *argv[] = { NULL, NULL };

	/* apply % substitution to cmd */
	struct strbuf cmd = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	struct strbuf_expand_dict_entry dict[] = {
		{ "f", NULL, },
		{ NULL, NULL, },
	};

	/* quote the path to preserve spaces, etc. */
	sq_quote_buf(&path, params->path);
	dict[0].value = path.buf;

	/* expand all %f with the quoted path */
	strbuf_expand(&cmd, params->cmd, strbuf_expand_dict_cb, &dict);
	strbuf_release(&path);

	argv[0] = cmd.buf;

	child_process.argv = argv;
	child_process.use_shell = 1;
	child_process.in = -1;
	child_process.out = out;

	if (start_command(&child_process))
		return error("cannot fork to run external filter '%s'", params->cmd);

	sigchain_push(SIGPIPE, SIG_IGN);

	if (params->src) {
		write_err = (write_in_full(child_process.in,
					   params->src, params->size) < 0);
		if (errno == EPIPE)
			write_err = 0;
	} else {
		write_err = copy_fd(params->fd, child_process.in);
		if (write_err == COPY_WRITE_ERROR && errno == EPIPE)
			write_err = 0;
	}

	if (close(child_process.in))
		write_err = 1;
	if (write_err)
		error("cannot feed the input to external filter '%s'", params->cmd);

	sigchain_pop(SIGPIPE);

	status = finish_command(&child_process);
	if (status)
		error("external filter '%s' failed %d", params->cmd, status);

	strbuf_release(&cmd);
	return (write_err || status);
}