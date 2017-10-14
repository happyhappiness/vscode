ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, f->c,
                      "coalesce: have %" APR_SIZE_T_FMT " bytes, "
                      "adding %" APR_SIZE_T_FMT " more", ctx->bytes, bytes);