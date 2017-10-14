ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                                      "Zlib: Length %ld of inflated data does "
                                      "not match expected value %ld",
                                      ctx->stream.total_out, compLen);