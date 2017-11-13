ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01789)
                      "unknown algorithm `%s' received: %s",
                      resp->algorithm, r->uri);