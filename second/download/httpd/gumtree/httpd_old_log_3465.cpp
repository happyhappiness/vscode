ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                     "Cannot open socache DBM file `%s' for reading "
                     "(fetch)",
                     ctx->data_file);