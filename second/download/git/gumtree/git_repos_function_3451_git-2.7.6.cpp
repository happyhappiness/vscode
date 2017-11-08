static int imap_store_msg(struct imap_store *ctx, struct strbuf *msg)
{
	struct imap *imap = ctx->imap;
	struct imap_cmd_cb cb;
	const char *prefix, *box;
	int ret;

	lf_to_crlf(msg);
	memset(&cb, 0, sizeof(cb));

	cb.dlen = msg->len;
	cb.data = strbuf_detach(msg, NULL);

	box = ctx->name;
	prefix = !strcmp(box, "INBOX") ? "" : ctx->prefix;
	ret = imap_exec_m(ctx, &cb, "APPEND \"%s%s\" ", prefix, box);
	imap->caps = imap->rcaps;
	if (ret != DRV_OK)
		return ret;

	return DRV_OK;
}