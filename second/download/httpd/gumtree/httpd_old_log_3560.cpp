ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot store socache object to DBM file `%s'",
                     ctx->data_file);