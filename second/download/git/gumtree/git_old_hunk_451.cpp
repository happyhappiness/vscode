	child_process.argv = argv;
	child_process.use_shell = 1;
	child_process.in = -1;
	child_process.out = out;

	if (start_command(&child_process))
		return error("cannot fork to run external filter %s", params->cmd);

	sigchain_push(SIGPIPE, SIG_IGN);

	if (params->src) {
		write_err = (write_in_full(child_process.in,
					   params->src, params->size) < 0);
