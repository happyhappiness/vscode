ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot create socache DBM file `%s'",
                     ctx->data_file);