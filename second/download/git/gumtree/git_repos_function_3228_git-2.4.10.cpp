static int socket_read(struct imap_socket *sock, char *buf, int len)
{
	ssize_t n;
#ifndef NO_OPENSSL
	if (sock->ssl)
		n = SSL_read(sock->ssl, buf, len);
	else
#endif
		n = xread(sock->fd[0], buf, len);
	if (n <= 0) {
		socket_perror("read", sock, n);
		close(sock->fd[0]);
		close(sock->fd[1]);
		sock->fd[0] = sock->fd[1] = -1;
	}
	return n;
}