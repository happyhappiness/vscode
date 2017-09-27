
    /* OpenSSL is not expected to call us with modes other than 1 or 0 */
    return -1;
}
#endif /* HAVE_TLS_SESSION_TICKETS */

#ifdef HAVE_SRP

int ssl_callback_SRPServerParams(SSL *ssl, int *ad, void *arg)
{
    modssl_ctx_t *mctx = (modssl_ctx_t *)arg;
    char *username = SSL_get_srp_username(ssl);
