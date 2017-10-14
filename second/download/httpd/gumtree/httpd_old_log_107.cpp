ap_log_error(APLOG_MARK, APLOG_ERR, 0, 
                             c->base_server,
                             "SSL handshake failed (server %s, client %s)",
                             ssl_util_vhostid(c->pool, c->base_server),
                             c->remote_ip ? c->remote_ip : "unknown");