static int imap_exec_m(struct imap_store *ctx, struct imap_cmd_cb *cb,
		       const char *fmt, ...)
{
	va_list ap;
	struct imap_cmd *cmdp;

	va_start(ap, fmt);
	cmdp = issue_imap_cmd(ctx, cb, fmt, ap);
	va_end(ap);
	if (!cmdp)
		return DRV_STORE_BAD;

	switch (get_cmd_result(ctx, cmdp)) {
	case RESP_BAD: return DRV_STORE_BAD;
	case RESP_NO: return DRV_MSG_BAD;
	default: return DRV_OK;
	}
}