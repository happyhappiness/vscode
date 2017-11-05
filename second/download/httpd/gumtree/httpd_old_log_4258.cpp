ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 SSLPROXY_CERT_CB_LOG_FMT "%s, sending %s",
                 sc->vhost_id, msg, dn ? dn : "-uknown-");