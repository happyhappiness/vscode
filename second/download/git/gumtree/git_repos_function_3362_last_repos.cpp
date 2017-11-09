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