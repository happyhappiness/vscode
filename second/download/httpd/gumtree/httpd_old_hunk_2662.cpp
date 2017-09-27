                if (zRC == Z_STREAM_END) {
                    break;
                }

                if (zRC != Z_OK) {
                    inflateEnd(&ctx->stream);
                    return APR_EGENERAL;
                }
            }
            if (zRC == Z_STREAM_END) {
                apr_bucket *tmp_heap, *eos;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Zlib: Inflated %ld to %ld : URL %s",
                              ctx->stream.total_in, ctx->stream.total_out,
                              r->uri);

                len = c->bufferSize - ctx->stream.avail_out;

