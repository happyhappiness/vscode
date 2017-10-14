ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot re-open socache DBM file `%s' for "
                         "expiring",
                         ctx->data_file);