ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
                      "failed to write %" APR_SSIZE_T_FMT
                      " of %" APR_SIZE_T_FMT " bytes (%s)",
                      len - (apr_size_t)res, len, reason);