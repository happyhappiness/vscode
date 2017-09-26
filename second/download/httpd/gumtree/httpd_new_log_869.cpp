ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "SSL Proxy requested for %s but not enabled "
                      "[Hint: SSLProxyEngine]", sc->vhost_id);