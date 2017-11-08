static inline int mingw_SSL_set_rfd(SSL *ssl, int fd)
{
	return SSL_set_rfd(ssl, _get_osfhandle(fd));
}