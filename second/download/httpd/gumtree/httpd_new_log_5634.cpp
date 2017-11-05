ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
                          r,
                          ref ? APLOGNO(03224) "Fixed spelling: %s to %s from %s"
                              : APLOGNO(03225) "Fixed spelling: %s to %s%s",
                          r->uri, nuri,
                          (ref ? ref : ""));