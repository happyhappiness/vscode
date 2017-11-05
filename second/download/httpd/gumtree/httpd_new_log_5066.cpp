ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                    "*: rewrite of url due to UDS(%s): %s (%s)",
                    sockpath, *url, r->filename);