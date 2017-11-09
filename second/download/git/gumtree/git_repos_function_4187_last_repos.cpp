static void imap_close_store(struct imap_store *ctx)
{
	imap_close_server(ctx);
	free(ctx);
}