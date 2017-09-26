ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Zlib: Invalid flags %02x", ctx->zlib_flags);