	}
	if (!svc->enabled)
		forbidden("Service not enabled: '%s'", svc->name);
	return svc;
}

/*
 * This is basically strbuf_read(), except that if we
 * hit max_request_buffer we die (we'd rather reject a
 * maliciously large request than chew up infinite memory).
 */
static ssize_t read_request(int fd, unsigned char **out)
{
	size_t len = 0, alloc = 8192;
	unsigned char *buf = xmalloc(alloc);

	if (max_request_buffer < alloc)
		max_request_buffer = alloc;

	while (1) {
		ssize_t cnt;

		cnt = read_in_full(fd, buf + len, alloc - len);
		if (cnt < 0) {
			free(buf);
			return -1;
		}

		/* partial read from read_in_full means we hit EOF */
		len += cnt;
		if (len < alloc) {
			*out = buf;
			return len;
		}

		/* otherwise, grow and try again (if we can) */
		if (alloc == max_request_buffer)
			die("request was larger than our maximum size (%lu);"
			    " try setting GIT_HTTP_MAX_REQUEST_BUFFER",
			    max_request_buffer);

		alloc = alloc_nr(alloc);
		if (alloc > max_request_buffer)
			alloc = max_request_buffer;
		REALLOC_ARRAY(buf, alloc);
	}
}

static void inflate_request(const char *prog_name, int out, int buffer_input)
{
	git_zstream stream;
	unsigned char *full_request = NULL;
	unsigned char in_buf[8192];
	unsigned char out_buf[8192];
	unsigned long cnt = 0;

	memset(&stream, 0, sizeof(stream));
	git_inflate_init_gzip_only(&stream);

	while (1) {
		ssize_t n;

		if (buffer_input) {
			if (full_request)
				n = 0; /* nothing left to read */
			else
				n = read_request(0, &full_request);
			stream.next_in = full_request;
		} else {
			n = xread(0, in_buf, sizeof(in_buf));
			stream.next_in = in_buf;
		}

		if (n <= 0)
			die("request ended in the middle of the gzip stream");
		stream.avail_in = n;

		while (0 < stream.avail_in) {
			int ret;

			stream.next_out = out_buf;
