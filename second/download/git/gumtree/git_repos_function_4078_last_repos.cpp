static int process_connect_service(struct transport *transport,
				   const char *name, const char *exec)
{
	struct helper_data *data = transport->data;
	struct strbuf cmdbuf = STRBUF_INIT;
	struct child_process *helper;
	int r, duped, ret = 0;
	FILE *input;

	helper = get_helper(transport);

	/*
	 * Yes, dup the pipe another time, as we need unbuffered version
	 * of input pipe as FILE*. fclose() closes the underlying fd and
	 * stream buffering only can be changed before first I/O operation
	 * on it.
	 */
	duped = dup(helper->out);
	if (duped < 0)
		die_errno("Can't dup helper output fd");
	input = xfdopen(duped, "r");
	setvbuf(input, NULL, _IONBF, 0);

	/*
	 * Handle --upload-pack and friends. This is fire and forget...
	 * just warn if it fails.
	 */
	if (strcmp(name, exec)) {
		r = set_helper_option(transport, "servpath", exec);
		if (r > 0)
			warning("Setting remote service path not supported by protocol.");
		else if (r < 0)
			warning("Invalid remote service path.");
	}

	if (data->connect)
		strbuf_addf(&cmdbuf, "connect %s\n", name);
	else
		goto exit;

	sendline(data, &cmdbuf);
	if (recvline_fh(input, &cmdbuf, name))
		exit(128);

	if (!strcmp(cmdbuf.buf, "")) {
		data->no_disconnect_req = 1;
		if (debug)
			fprintf(stderr, "Debug: Smart transport connection "
				"ready.\n");
		ret = 1;
	} else if (!strcmp(cmdbuf.buf, "fallback")) {
		if (debug)
			fprintf(stderr, "Debug: Falling back to dumb "
				"transport.\n");
	} else
		die("Unknown response to connect: %s",
			cmdbuf.buf);

exit:
	fclose(input);
	return ret;
}