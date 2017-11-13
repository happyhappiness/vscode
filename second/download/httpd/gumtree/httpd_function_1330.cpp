int ssl_callback_ServerNameIndication(SSL *ssl, int *al, modssl_ctx_t *mctx)
{
    const char *servername =
                SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);

    if (servername) {
        conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
        if (c) {
            if (ap_vhost_iterate_given_conn(c, ssl_find_vhost,
                                            (void *)servername)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "SSL virtual host for servername %s found",
                              servername);
                return SSL_TLSEXT_ERR_OK;
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "No matching SSL virtual host for servername "
                              "%s found (using default/first virtual host)",
                              servername);
                return SSL_TLSEXT_ERR_ALERT_WARNING;
            }
        }
    }

    return SSL_TLSEXT_ERR_NOACK;
}