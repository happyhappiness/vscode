		}
		free(buf);
		close(po.out);
		po.out = -1;
	}

	rc = finish_command(&po);
	if (rc) {
		/*
		 * For a normal non-zero exit, we assume pack-objects wrote
		 * something useful to stderr. For death by signal, though,
		 * we should mention it to the user. The exception is SIGPIPE
		 * (141), because that's a normal occurence if the remote end
		 * hangs up (and we'll report that by trying to read the unpack
		 * status).
		 */
		if (rc > 128 && rc != 141)
			error("pack-objects died of signal %d", rc - 128);
		return -1;
	}
	return 0;
}

static int receive_unpack_status(int in)
{
	const char *line = packet_read_line(in, NULL);
	if (!skip_prefix(line, "unpack ", &line))
		return error(_("unable to parse remote unpack status: %s"), line);
	if (strcmp(line, "ok"))
		return error(_("remote unpack failed: %s"), line);
	return 0;
}

static int receive_status(int in, struct ref *refs)
{
	struct ref *hint;
	int ret;

	hint = NULL;
	ret = receive_unpack_status(in);
	while (1) {
		char *refname;
		char *msg;
		char *line = packet_read_line(in, NULL);
		if (!line)
			break;
		if (!starts_with(line, "ok ") && !starts_with(line, "ng ")) {
			error("invalid ref status from remote: %s", line);
			ret = -1;
			break;
