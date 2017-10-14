ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                     "Cannot open socache DBM file `%s' for status "
                     "retrival",
                     ctx->data_file);