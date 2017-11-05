ap_log_error(APLOG_MARK, APLOG_INFO, rc, c->base_server,
                         "SSL library error %d in handshake "
                         "(server %s, client %s)", ssl_err,
                         ssl_util_vhostid(c->pool, c->base_server),
                         c->remote_ip ? c->remote_ip : "unknown");