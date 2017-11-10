static int send_request(const char *socket, const struct strbuf *out)
{
	int got_data = 0;
	int fd = unix_stream_connect(socket);

	if (fd < 0)
		return -1;

	if (write_in_full(fd, out->buf, out->len) < 0)
		die_errno("unable to write to cache daemon");
	shutdown(fd, SHUT_WR);

	while (1) {
		char in[1024];
		int r;

		r = read_in_full(fd, in, sizeof(in));
		if (r == 0)
			break;
		if (r < 0)
			die_errno("read error from cache daemon");
		write_or_die(1, in, r);
		got_data = 1;
	}
	return got_data;
}