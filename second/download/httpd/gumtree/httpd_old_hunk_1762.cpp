
static void ssl_configure_env(request_rec *r, SSLConnRec *sslconn);
#ifndef OPENSSL_NO_TLSEXT
static int ssl_find_vhost(void *servername, conn_rec *c, server_rec *s);
#endif

/* Perform a speculative (and non-blocking) read from the connection
 * filters for the given request, to determine whether there is any
 * pending data to read.  Return non-zero if there is, else zero. */
static int has_buffered_data(request_rec *r) 
{
    apr_bucket_brigade *bb;
