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
