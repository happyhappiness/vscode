ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: client used wrong authentication scheme "
                          "`%s': %s", resp->scheme, r->uri);