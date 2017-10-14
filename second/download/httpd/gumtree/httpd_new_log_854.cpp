ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                          "SSL library error %d in handshake "
                          "(server %s)", ssl_err,
                          ssl_util_vhostid(c->pool, c->base_server));