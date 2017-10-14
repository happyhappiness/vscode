ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01788)
                      "realm mismatch - got `%s' but expected `%s'",
                      resp->realm, conf->realm);