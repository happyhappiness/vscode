ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Timeout while writing data for URI %s to the"
                          " client", r->unparsed_uri);