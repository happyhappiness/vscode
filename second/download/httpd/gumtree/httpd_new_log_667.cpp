ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              "regex capture $%" APR_SIZE_T_FMT
                              " is out of range (last regex was: '%s') in %s",
                              idx, re->rexp, r->filename);