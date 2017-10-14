ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: unknown algorithm `%s' received: %s",
                      resp->algorithm, r->uri);