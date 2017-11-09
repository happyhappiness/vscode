static int ssl_socket_connect(struct imap_socket *sock, int use_tls_only, int verify)
{
	fprintf(stderr, "SSL requested but SSL support not compiled in\n");
	return -1;
}