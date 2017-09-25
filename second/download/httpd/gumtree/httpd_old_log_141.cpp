ap_log_error(APLOG_MARK, APLOG_INFO, 0, conn->base_server,
                     "Connection to child %ld closed with %s shutdown"
                     "(server %s, client %s)",
                     conn->id, type,
                     ssl_util_vhostid(conn->pool, conn->base_server),
                     conn->remote_ip ? conn->remote_ip : "unknown");