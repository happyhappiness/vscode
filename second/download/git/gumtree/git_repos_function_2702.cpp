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
			stream.avail_out = sizeof(out_buf);

			ret = git_inflate(&stream, Z_NO_FLUSH);
			if (ret != Z_OK && ret != Z_STREAM_END)
				die("zlib error inflating request, result %d", ret);

			n = stream.total_out - cnt;
			if (write_in_full(out, out_buf, n) != n)
				die("%s aborted reading request", prog_name);
			cnt += n;

			if (ret == Z_STREAM_END)
				goto done;
		}
	}

done:
	git_inflate_end(&stream);
	close(out);
	free(full_request);
}