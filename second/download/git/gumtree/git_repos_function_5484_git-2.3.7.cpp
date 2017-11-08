static inline int mingw_SSL_set_wfd(SSL *ssl, int fd)
{
	return SSL_set_wfd(ssl, _get_osfhandle(fd));
}