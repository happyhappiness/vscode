ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01384)
                          "Zlib: Compressed %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);