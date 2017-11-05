ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Zlib error %d deflating data (%s)", zRC,
                              ctx->stream.msg);