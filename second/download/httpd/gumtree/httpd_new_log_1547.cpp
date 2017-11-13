ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);