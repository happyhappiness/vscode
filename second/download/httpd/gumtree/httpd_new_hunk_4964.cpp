                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);
                    return APR_EGENERAL;
                }
            }
            if (zRC == Z_STREAM_END) {
                apr_bucket *tmp_heap;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01393)
                              "Zlib: Inflated %ld to %ld : URL %s",
                              ctx->stream.total_in, ctx->stream.total_out,
                              r->uri);

