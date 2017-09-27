ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01407)
                              "Zlib: %d bytes of garbage at the end of "
                              "compressed stream.", ctx->stream.avail_in);