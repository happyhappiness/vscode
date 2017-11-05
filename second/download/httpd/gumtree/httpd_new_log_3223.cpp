ap_log_rerror(APLOG_MARK, lvl, rv, r, APLOGNO(01466)
                      "apr_file_read(child output), len %" APR_SIZE_T_FMT,
                      !rv ? len : -1);