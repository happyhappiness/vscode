static struct imap_cmd *issue_imap_cmd(struct imap_store *ctx,
				       struct imap_cmd_cb *cb,
				       const char *fmt, va_list ap)
{
	struct imap *imap = ctx->imap;
	struct imap_cmd *cmd;
	int n, bufl;
	char buf[1024];

	cmd = xmalloc(sizeof(struct imap_cmd));
	nfvasprintf(&cmd->cmd, fmt, ap);
	cmd->tag = ++imap->nexttag;

	if (cb)
		cmd->cb = *cb;
	else
		memset(&cmd->cb, 0, sizeof(cmd->cb));

	while (imap->literal_pending)
		get_cmd_result(ctx, NULL);

	if (!cmd->cb.data)
		bufl = nfsnprintf(buf, sizeof(buf), "%d %s\r\n", cmd->tag, cmd->cmd);
	else
		bufl = nfsnprintf(buf, sizeof(buf), "%d %s{%d%s}\r\n",
				  cmd->tag, cmd->cmd, cmd->cb.dlen,
				  CAP(LITERALPLUS) ? "+" : "");

	if (0 < verbosity) {
		if (imap->num_in_progress)
			printf("(%d in progress) ", imap->num_in_progress);
		if (!starts_with(cmd->cmd, "LOGIN"))
			printf(">>> %s", buf);
		else
			printf(">>> %d LOGIN <user> <pass>\n", cmd->tag);
	}
	if (socket_write(&imap->buf.sock, buf, bufl) != bufl) {
		free(cmd->cmd);
		free(cmd);
		if (cb)
			free(cb->data);
		return NULL;
	}
	if (cmd->cb.data) {
		if (CAP(LITERALPLUS)) {
			n = socket_write(&imap->buf.sock, cmd->cb.data, cmd->cb.dlen);
			free(cmd->cb.data);
			if (n != cmd->cb.dlen ||
			    socket_write(&imap->buf.sock, "\r\n", 2) != 2) {
				free(cmd->cmd);
				free(cmd);
				return NULL;
			}
			cmd->cb.data = NULL;
		} else
			imap->literal_pending = 1;
	} else if (cmd->cb.cont)
		imap->literal_pending = 1;
	cmd->next = NULL;
	*imap->in_progress_append = cmd;
	imap->in_progress_append = &cmd->next;
	imap->num_in_progress++;
	return cmd;
}