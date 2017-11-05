int ssl_callback_ServerNameIndication(SSL *ssl, int *al, modssl_ctx_t *mctx)
{
    const char *servername =
                SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);

    if (c) {
        if (servername) {
            if (ap_vhost_iterate_given_conn(c, ssl_find_vhost,
                                            (void *)servername)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02043)
                              "SSL virtual host for servername %s found",
                              servername);
                return SSL_TLSEXT_ERR_OK;
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02044)
                              "No matching SSL virtual host for servername "
                              "%s found (using default/first virtual host)",
                              servername);
                /*
                 * RFC 6066 section 3 says "It is NOT RECOMMENDED to send
                 * a warning-level unrecognized_name(112) alert, because
                 * the client's behavior in response to warning-level alerts
                 * is unpredictable."
                 *
                 * To maintain backwards compatibility in mod_ssl, we
                 * no longer send any alert (neither warning- nor fatal-level),
                 * i.e. we take the second action suggested in RFC 6066:
                 * "If the server understood the ClientHello extension but
                 * does not recognize the server name, the server SHOULD take
                 * one of two actions: either abort the handshake by sending
                 * a fatal-level unrecognized_name(112) alert or continue
                 * the handshake."
                 */
            }
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02645)
                          "Server name not provided via TLS extension "
                          "(using default/first virtual host)");
        }
    }

    return SSL_TLSEXT_ERR_NOACK;
}