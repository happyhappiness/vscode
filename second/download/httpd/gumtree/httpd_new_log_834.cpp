ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                  "Connection to child %ld established "
                  "(server %s)", c->id, sc->vhost_id);