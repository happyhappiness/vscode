{
	int ret;
	va_list va;

	va_start(va, fmt);
	if (blen <= 0 || (unsigned)(ret = vsnprintf(buf, blen, fmt, va)) >= (unsigned)blen)
		die("Fatal: buffer too small. Please report a bug.");
	va_end(va);
	return ret;
}

static struct imap_cmd *issue_imap_cmd(struct imap_store *ctx,
				       struct imap_cmd_cb *cb,
