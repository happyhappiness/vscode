static int apply_single_file_filter(const char *path, const char *src, size_t len, int fd,
                        struct strbuf *dst, const char *cmd)
{
	/*
	 * Create a pipeline to have the command filter the buffer's
	 * contents.
	 *
	 * (child --> cmd) --> us
	 */
	int err = 0;
	struct strbuf nbuf = STRBUF_INIT;
	struct async async;
	struct filter_params params;

	memset(&async, 0, sizeof(async));
	async.proc = filter_buffer_or_fd;
	async.data = &params;
	async.out = -1;
	params.src = src;
	params.size = len;
	params.fd = fd;
	params.cmd = cmd;
	params.path = path;

	fflush(NULL);
	if (start_async(&async))
		return 0;	/* error was already reported */

	if (strbuf_read(&nbuf, async.out, len) < 0) {
		err = error("read from external filter '%s' failed", cmd);
	}
	if (close(async.out)) {
		err = error("read from external filter '%s' failed", cmd);
	}
	if (finish_async(&async)) {
		err = error("external filter '%s' failed", cmd);
	}

	if (!err) {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return !err;
}