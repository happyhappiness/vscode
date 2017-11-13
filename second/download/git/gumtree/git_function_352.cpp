static int run_remote_archiver(int argc, const char **argv,
			       const char *remote, const char *exec,
			       const char *name_hint)
{
	char *buf;
	int fd[2], i, rv;
	struct transport *transport;
	struct remote *_remote;

	_remote = remote_get(remote);
	if (!_remote->url[0])
		die(_("git archive: Remote with no URL"));
	transport = transport_get(_remote, _remote->url[0]);
	transport_connect(transport, "git-upload-archive", exec, fd);

	/*
	 * Inject a fake --format field at the beginning of the
	 * arguments, with the format inferred from our output
	 * filename. This way explicit --format options can override
	 * it.
	 */
	if (name_hint) {
		const char *format = archive_format_from_filename(name_hint);
		if (format)
			packet_write(fd[1], "argument --format=%s\n", format);
	}
	for (i = 1; i < argc; i++)
		packet_write(fd[1], "argument %s\n", argv[i]);
	packet_flush(fd[1]);

	buf = packet_read_line(fd[0], NULL);
	if (!buf)
		die(_("git archive: expected ACK/NAK, got EOF"));
	if (strcmp(buf, "ACK")) {
		if (starts_with(buf, "NACK "))
			die(_("git archive: NACK %s"), buf + 5);
		if (starts_with(buf, "ERR "))
			die(_("remote error: %s"), buf + 4);
		die(_("git archive: protocol error"));
	}

	if (packet_read_line(fd[0], NULL))
		die(_("git archive: expected a flush"));

	/* Now, start reading from fd[0] and spit it out to stdout */
	rv = recv_sideband("archive", fd[0], 1);
	rv |= transport_disconnect(transport);

	return !!rv;
}