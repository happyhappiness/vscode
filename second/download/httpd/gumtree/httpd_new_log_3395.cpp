ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01584)
                          "copy_brigade_range() failed [%" APR_OFF_T_FMT
                          "-%" APR_OFF_T_FMT ",%" APR_OFF_T_FMT "]",
                          range_start, range_end, clength);