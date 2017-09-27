(r->server != handshakeserver) {
                /* 
                 * We are really not in Kansas anymore...
                 * The request does not select the virtual host that was
                 * selected by the SNI.
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
                             "Hostname %s provided via SNI and hostname %s provided"
                             " via HTTP select a different server",
                             servername, r->hostname);
                return HTTP_MISDIRECTED_REQUEST;
            };