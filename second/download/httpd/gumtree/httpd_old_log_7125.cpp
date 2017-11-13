ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
                          r,
                          ref ? "Fixed spelling: %s to %s from %s"
                              : "Fixed spelling: %s to %s",
                          r->uri, nuri, ref);