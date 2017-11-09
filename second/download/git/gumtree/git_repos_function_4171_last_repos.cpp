static int socket_write(struct imap_socket *sock, const char *buf, int len)
{
	int n;
#ifndef NO_OPENSSL
	if (sock->ssl)
		n = SSL_write(sock->ssl, buf, len);
	else
#endif
		n = write_in_full(sock->fd[1], buf, len);
	if (n != len) {
		socket_perror("write", sock, n);
		close(sock->fd[0]);
		close(sock->fd[1]);
		sock->fd[0] = sock->fd[1] = -1;
	}
	return n;
}