static void socket_shutdown(struct imap_socket *sock)
{
#ifndef NO_OPENSSL
	if (sock->ssl) {
		SSL_shutdown(sock->ssl);
		SSL_free(sock->ssl);
	}
#endif
	close(sock->fd[0]);
	close(sock->fd[1]);
}