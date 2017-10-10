		error("external filter %s failed %d", params->cmd, status);

	strbuf_release(&cmd);
	return (write_err || status);
}

static int apply_filter(const char *path, const char *src, size_t len,
                        struct strbuf *dst, const char *cmd)
{
	/*
	 * Create a pipeline to have the command filter the buffer's
	 * contents.
	 *
