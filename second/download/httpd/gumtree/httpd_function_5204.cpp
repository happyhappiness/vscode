int ssl_callback_alpn_select(SSL *ssl,
                             const unsigned char **out, unsigned char *outlen,
                             const unsigned char *in, unsigned int inlen,
                             void *arg)
{
    conn_rec *c = (conn_rec*)SSL_get_app_data(ssl);
    SSLConnRec *sslconn = myConnConfig(c);
    apr_array_header_t *client_protos;
    const char *proposed;
    size_t len;
    int i;

    /* If the connection object is not available,
     * then there's nothing for us to do. */
    if (c == NULL) {
        return SSL_TLSEXT_ERR_OK;
    }

    if (inlen == 0) {
        /* someone tries to trick us? */
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02837)
                      "ALPN client protocol list empty");
        return SSL_TLSEXT_ERR_ALERT_FATAL;
    }

    client_protos = apr_array_make(c->pool, 0, sizeof(char *));
    for (i = 0; i < inlen; /**/) {
        unsigned int plen = in[i++];
        if (plen + i > inlen) {
            /* someone tries to trick us? */
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02838)
                          "ALPN protocol identifier too long");
            return SSL_TLSEXT_ERR_ALERT_FATAL;
        }
        APR_ARRAY_PUSH(client_protos, char *) =
            apr_pstrndup(c->pool, (const char *)in+i, plen);
        i += plen;
    }

    /* The order the callbacks are invoked from TLS extensions is, unfortunately
     * not defined and older openssl versions do call ALPN selection before
     * they callback the SNI. We need to make sure that we know which vhost
     * we are dealing with so we respect the correct protocols.
     */
    init_vhost(c, ssl);
    
    proposed = ap_select_protocol(c, NULL, sslconn->server, client_protos);
    *out = (const unsigned char *)(proposed? proposed : ap_get_protocol(c));
    len = strlen((const char*)*out);
    if (len > 255) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02840)
                      "ALPN negotiated protocol name too long");
        return SSL_TLSEXT_ERR_ALERT_FATAL;
    }
    *outlen = (unsigned char)len;

    return SSL_TLSEXT_ERR_OK;
}