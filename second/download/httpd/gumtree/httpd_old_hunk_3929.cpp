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
