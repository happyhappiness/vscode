ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                      "Connection closed to child %ld with %s shutdown "
                      "(server %s)",
                      c->id, type, ssl_util_vhostid(c->pool, c->base_server));