ap_log_cerror(APLOG_MARK, loglevel, 0, c,
                      "Connection closed to child %ld with %s shutdown "
                      "(server %s)",
                      c->id, type, ssl_util_vhostid(c->pool, mySrvFromConn(c)));