ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01385)
                              "Zlib error %d flushing zlib output buffer (%s)",
                              zRC, ctx->stream.msg);