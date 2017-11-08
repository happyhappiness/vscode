static int ssl_io_hook_read(SSL *ssl, char *buf, int len)
{
    int rc;

    if (ssl == NULL) {
        return -1;
    }

    rc = SSL_read(ssl, buf, len);

    if (rc <= 0) {
        int ssl_err = SSL_get_error(ssl, rc);

        if (ssl_err == SSL_ERROR_WANT_READ) {
            /*
             * Simulate an EINTR in case OpenSSL wants to read more.
             * (This is usually the case when the client forces an SSL
             * renegotation which is handled implicitly by OpenSSL.)
             */
            errno = EINTR;
            rc = 0; /* non fatal error */
        }
        else if (ssl_err == SSL_ERROR_SSL) {
            /*
             * Log SSL errors
             */
            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                    "SSL error on reading data");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
        }
    }

    return rc;
}