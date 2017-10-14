ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01409)
                              "Zlib error %d inflating data (%s)", zRC,
                              ctx->stream.msg);