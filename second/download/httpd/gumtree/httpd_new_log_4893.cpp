ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02268)
                     SSLPROXY_CERT_CB_LOG_FMT
                     "downstream server wanted client certificate "
                     "but none are configured", sc->vhost_id);