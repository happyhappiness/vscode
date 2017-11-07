static int auth_cram_md5(struct imap_store *ctx, struct imap_cmd *cmd, const char *prompt)
{
	int ret;
	char *response;

	response = cram(prompt, server.user, server.pass);

	ret = socket_write(&ctx->imap->buf.sock, response, strlen(response));
	if (ret != strlen(response))
		return error("IMAP error: sending response failed");

	free(response);

	return 0;
}