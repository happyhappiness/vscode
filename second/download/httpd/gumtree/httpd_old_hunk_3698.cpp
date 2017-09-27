                            " is larger than the configured limit"
                            " of %" APR_OFF_T_FMT, 
                            ctx->inflate_total, inflate_limit);
                    return APR_ENOSPC;
                }

                ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                tmp_b = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                NULL, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_b);
                ctx->stream.avail_out = c->bufferSize;

