ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                     "SSL Proxy requested for %s but not enabled "
                     "[Hint: SSLProxyEngine]", sc->vhost_id);