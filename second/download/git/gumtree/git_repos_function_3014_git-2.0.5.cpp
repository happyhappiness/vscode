static struct imap_cmd *issue_imap_cmd(struct imap_store *ctx,
				       struct imap_cmd_cb *cb,
				       const char *fmt, ...)
{
	struct imap_cmd *ret;
	va_list ap;

	va_start(ap, fmt);
	ret = v_issue_imap_cmd(ctx, cb, fmt, ap);
	va_end(ap);
	return ret;
}