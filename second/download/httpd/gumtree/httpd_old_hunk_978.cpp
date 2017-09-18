                             "Re-negotiation handshake failed: "
                             "Client verification failed");

                return HTTP_FORBIDDEN;
            }

            if (do_verify &&
                ((cert = SSL_get_peer_certificate(ssl)) == NULL)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation handshake failed: "
                             "Client certificate missing");

                return HTTP_FORBIDDEN;
            }
        }
    }

    /*
     * Check SSLRequire boolean expressions
