int ssl_hook_ReadReq(request_rec *r)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);
    SSLConnRec *sslconn;
    const char *upgrade;
#ifdef HAVE_TLSEXT
    const char *servername;
#endif
    SSL *ssl;

    /* Perform TLS upgrade here if "SSLEngine optional" is configured,
     * SSL is not already set up for this connection, and the client
     * has sent a suitable Upgrade header. */
    if (sc->enabled == SSL_ENABLED_OPTIONAL && !myConnConfig(r->connection)
        && (upgrade = apr_table_get(r->headers_in, "Upgrade")) != NULL
        && ap_find_token(r->pool, upgrade, "TLS/1.0")) {
        if (upgrade_connection(r)) {
            return AP_FILTER_ERROR;
        }
    }

    sslconn = myConnConfig(r->connection);
    if (!sslconn) {
        return DECLINED;
    }

    if (sslconn->non_ssl_request == NON_SSL_SET_ERROR_MSG) {
        apr_table_setn(r->notes, "error-notes",
                       "Reason: You're speaking plain HTTP to an SSL-enabled "
                       "server port.<br />\n Instead use the HTTPS scheme to "
                       "access this URL, please.<br />\n");

        /* Now that we have caught this error, forget it. we are done
         * with using SSL on this request.
         */
        sslconn->non_ssl_request = NON_SSL_OK;

        return HTTP_BAD_REQUEST;
    }

    /*
     * Get the SSL connection structure and perform the
     * delayed interlinking from SSL back to request_rec
     */
    ssl = sslconn->ssl;
    if (!ssl) {
        return DECLINED;
    }
#ifdef HAVE_TLSEXT
    /*
     * Perform SNI checks only on the initial request.  In particular,
     * if these checks detect a problem, the checks shouldn't return an
     * error again when processing an ErrorDocument redirect for the
     * original problem.
     */
    if (r->proxyreq != PROXYREQ_PROXY && ap_is_initial_req(r)) {
        if ((servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))) {
            char *host, *scope_id;
            apr_port_t port;
            apr_status_t rv;

            /*
             * The SNI extension supplied a hostname. So don't accept requests
             * with either no hostname or a different hostname as this could
             * cause us to end up in a different virtual host as the one that
             * was used for the handshake causing different SSL parameters to
             * be applied as SSLProtocol, SSLCACertificateFile/Path and
             * SSLCADNRequestFile/Path cannot be renegotiated (SSLCA* due
             * to current limitations in OpenSSL, see
             * http://mail-archives.apache.org/mod_mbox/httpd-dev/200806.mbox/%3C48592955.2090303@velox.ch%3E
             * and
             * http://mail-archives.apache.org/mod_mbox/httpd-dev/201312.mbox/%3CCAKQ1sVNpOrdiBm-UPw1hEdSN7YQXRRjeaT-MCWbW_7mN%3DuFiOw%40mail.gmail.com%3E
             * )
             */
            if (!r->hostname) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02031)
                            "Hostname %s provided via SNI, but no hostname"
                            " provided in HTTP request", servername);
                return HTTP_BAD_REQUEST;
            }
            rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
            if (rv != APR_SUCCESS || scope_id) {
                return HTTP_BAD_REQUEST;
            }
            if (strcasecmp(host, servername)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
                            "Hostname %s provided via SNI and hostname %s provided"
                            " via HTTP are different", servername, host);
                return HTTP_BAD_REQUEST;
            }
        }
        else if (((sc->strict_sni_vhost_check == SSL_ENABLED_TRUE)
                 || (mySrvConfig(sslconn->server))->strict_sni_vhost_check
                    == SSL_ENABLED_TRUE)
                 && r->connection->vhost_lookup_data) {
            /*
             * We are using a name based configuration here, but no hostname was
             * provided via SNI. Don't allow that if are requested to do strict
             * checking. Check whether this strict checking was set up either in the
             * server config we used for handshaking or in our current server.
             * This should avoid insecure configuration by accident.
             */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02033)
                         "No hostname was provided via SNI for a name based"
                         " virtual host");
            apr_table_setn(r->notes, "error-notes",
                           "Reason: The client software did not provide a "
                           "hostname using Server Name Indication (SNI), "
                           "which is required to access this server.<br />\n");
            return HTTP_FORBIDDEN;
        }
    }
#endif
    SSL_set_app_data2(ssl, r);

    /*
     * Log information about incoming HTTPS requests
     */
    if (APLOGrinfo(r) && ap_is_initial_req(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02034)
                     "%s HTTPS request received for child %ld (server %s)",
                     (r->connection->keepalives <= 0 ?
                     "Initial (No.1)" :
                     apr_psprintf(r->pool, "Subsequent (No.%d)",
                                  r->connection->keepalives+1)),
                     r->connection->id,
                     ssl_util_vhostid(r->pool, r->server));
    }

    /* SetEnvIf ssl-*-shutdown flags can only be per-server,
     * so they won't change across keepalive requests
     */
    if (sslconn->shutdown_type == SSL_SHUTDOWN_TYPE_UNSET) {
        ssl_configure_env(r, sslconn);
    }

    return DECLINED;
}