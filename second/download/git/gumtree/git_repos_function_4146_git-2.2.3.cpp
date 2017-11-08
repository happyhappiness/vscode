static void *get_data(unsigned long size)
{
	git_zstream stream;
	void *buf = xmalloc(size);

	memset(&stream, 0, sizeof(stream));

	stream.next_out = buf;
	stream.avail_out = size;
	stream.next_in = fill(1);
	stream.avail_in = len;
	git_inflate_init(&stream);

	for (;;) {
		int ret = git_inflate(&stream, 0);
		use(len - stream.avail_in);
		if (stream.total_out == size && ret == Z_STREAM_END)
			break;
		if (ret != Z_OK) {
			error("inflate returned %d", ret);
			free(buf);
			buf = NULL;
			if (!recover)
				exit(1);
			has_errors = 1;
			break;
		}
		stream.next_in = fill(1);
		stream.avail_in = len;
	}
	git_inflate_end(&stream);
	return buf;
}