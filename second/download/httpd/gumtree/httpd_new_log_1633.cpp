ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "TLS session ticket key for %s successfully set, "
                      "creating new session ticket", sc->vhost_id);