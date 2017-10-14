ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01791)
                      "user `%s' in realm `%s' denied by provider: %s",
                      r->user, conf->realm, r->uri);