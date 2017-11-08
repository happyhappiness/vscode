static int apply_filter(const char *path, const char *src, size_t len, int fd,
                        struct strbuf *dst, const char *cmd)
{
	/*
	 * Create a pipeline to have the command filter the buffer's
	 * contents.
	 *
	 * (child --> cmd) --> us
	 */
	int ret = 1;
	struct strbuf nbuf = STRBUF_INIT;
	struct async async;
	struct filter_params params;

	if (!cmd || !*cmd)
		return 0;

	if (!dst)
		return 1;

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
		error("read from external filter %s failed", cmd);
		ret = 0;
	}
	if (close(async.out)) {
		error("read from external filter %s failed", cmd);
		ret = 0;
	}
	if (finish_async(&async)) {
		error("external filter %s failed", cmd);
		ret = 0;
	}

	if (ret) {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return ret;
}