	}
	if (!svc->enabled)
		forbidden("Service not enabled: '%s'", svc->name);
	return svc;
}

static void inflate_request(const char *prog_name, int out)
{
	git_zstream stream;
	unsigned char in_buf[8192];
	unsigned char out_buf[8192];
	unsigned long cnt = 0;

	memset(&stream, 0, sizeof(stream));
	git_inflate_init_gzip_only(&stream);

	while (1) {
		ssize_t n = xread(0, in_buf, sizeof(in_buf));
		if (n <= 0)
			die("request ended in the middle of the gzip stream");

		stream.next_in = in_buf;
		stream.avail_in = n;

		while (0 < stream.avail_in) {
			int ret;

			stream.next_out = out_buf;
