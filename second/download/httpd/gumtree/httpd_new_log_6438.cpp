ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, error_fmt, tag_val,
                    r->filename, status ? status : rr ? rr->status : 0);