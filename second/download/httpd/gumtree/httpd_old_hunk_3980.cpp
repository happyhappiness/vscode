                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, bkt);
                break;
            }

            if (APR_BUCKET_IS_FLUSH(bkt)) {
                apr_bucket *tmp_b;
                zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
                if (zRC != Z_OK) {
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01391)
                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);
                    return APR_EGENERAL;
                }

                ctx->stream.next_out = ctx->buffer;
                len = c->bufferSize - ctx->stream.avail_out;
 
                ctx->inflate_total += len;
                if (inflate_limit && ctx->inflate_total > inflate_limit) { 
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02647)
                            "Inflated content length of %" APR_OFF_T_FMT
                            " is larger than the configured limit"
                            " of %" APR_OFF_T_FMT, 
