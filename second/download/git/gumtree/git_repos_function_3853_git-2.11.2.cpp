static void imap_close_server(struct imap_store *ictx)
{
	struct imap *imap = ictx->imap;

	if (imap->buf.sock.fd[0] != -1) {
		imap_exec(ictx, NULL, "LOGOUT");
		socket_shutdown(&imap->buf.sock);
	}
	free(imap);
}