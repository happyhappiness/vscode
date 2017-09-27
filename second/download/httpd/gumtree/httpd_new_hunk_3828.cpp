
    /* OpenSSL is not expected to call us with modes other than 1 or 0 */
    return -1;
}
#endif /* HAVE_TLS_SESSION_TICKETS */

#ifdef HAVE_TLS_ALPN

/*
 * This callback function is executed when the TLS Application-Layer
 * Protocol Negotiation Extension (ALPN, RFC 7301) is triggered by the Client
 * Hello, giving a list of desired protocol names (in descending preference) 
 * to the server.
 * The callback has to select a protocol name or return an error if none of
 * the clients preferences is supported.
 * The selected protocol does not have to be on the client list, according
 * to RFC 7301, so no checks are performed.
 * The client protocol list is serialized as length byte followed by ASCII
 * characters (not null-terminated), followed by the next protocol name.
 */
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
#endif /* HAVE_TLS_ALPN */

#ifdef HAVE_SRP

int ssl_callback_SRPServerParams(SSL *ssl, int *ad, void *arg)
{
    modssl_ctx_t *mctx = (modssl_ctx_t *)arg;
    char *username = SSL_get_srp_username(ssl);
