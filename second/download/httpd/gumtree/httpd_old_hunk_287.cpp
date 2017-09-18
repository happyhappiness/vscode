                return HTTP_BAD_REQUEST;
            }
            else if ((SSL_get_error(filter->pssl, n) == SSL_ERROR_SYSCALL) &&
                     (errno != EINTR))
            {
                if (errno > 0) {
                    ssl_log(c->base_server,
                            SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_ADD_ERRNO,
                            "SSL handshake interrupted by system "
                            "[Hint: Stop button pressed in browser?!]");
                }
                else {
                    ssl_log(c->base_server,
                            SSL_LOG_INFO|SSL_ADD_SSLERR|SSL_ADD_ERRNO,
                            "Spurious SSL handshake interrupt [Hint: "
                            "Usually just one of those OpenSSL confusions!?]");
                }
            }
            else {
                /*
                 * Ok, anything else is a fatal error
                 */
                ssl_log(c->base_server,
                        SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_ADD_ERRNO,
                        "SSL handshake failed (server %s, client %s)",
                        ssl_util_vhostid(c->pool, c->base_server),
                        c->remote_ip ? c->remote_ip : "unknown");
            }

            return ssl_abort(filter, c);
        }

        /*
