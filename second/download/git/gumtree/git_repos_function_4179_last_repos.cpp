static int imap_exec(struct imap_store *ctx, struct imap_cmd_cb *cb,
		     const char *fmt, ...)
{
	va_list ap;
	struct imap_cmd *cmdp;

	va_start(ap, fmt);
	cmdp = issue_imap_cmd(ctx, cb, fmt, ap);
	va_end(ap);
	if (!cmdp)
		return RESP_BAD;

	return get_cmd_result(ctx, cmdp);
}