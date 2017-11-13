ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Failure reading first/next socache DBM file `%s' record",
                     ctx->data_file);