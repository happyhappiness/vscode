ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01329)
                "regex capture $%" APR_SIZE_T_FMT " refers to no regex in %s",
                idx, r->filename);