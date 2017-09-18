                return HTTP_BAD_REQUEST;
            }
            else if ((SSL_get_error(filter->pssl, n) == SSL_ERROR_SYSCALL) &&
                     (errno != EINTR))
            {
                if (errno > 0) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                 c->base_server,
                                 "SSL handshake interrupted by system "
                                 "[Hint: Stop button pressed in browser?!]");
                    ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, 
                                 c->base_server,
                                 "Spurious SSL handshake interrupt [Hint: "
                                 "Usually just one of those OpenSSL "
                                 "confusions!?]");
                    ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
                }
            }
            else {
                /*
                 * Ok, anything else is a fatal error
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, 
                             c->base_server,
                             "SSL handshake failed (server %s, client %s)",
                             ssl_util_vhostid(c->pool, c->base_server),
                             c->remote_ip ? c->remote_ip : "unknown");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
            }

            return ssl_abort(filter, c);
        }

        /*
