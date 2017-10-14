ap_log_cserror(APLOG_MARK, loglevel, 0, c, mySrvFromConn(c),
                       "Connection closed to child %ld with %s shutdown "
                       "(server %s)",
                       c->id, type,
                       ssl_util_vhostid(c->pool, mySrvFromConn(c)));