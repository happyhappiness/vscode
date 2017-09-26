ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
                     "Connection to child %ld closed with %s shutdown"
                     "(server %s, client %s)",
                     c->id, type,
                     ssl_util_vhostid(c->pool, c->base_server),
                     c->remote_ip ? c->remote_ip : "unknown");