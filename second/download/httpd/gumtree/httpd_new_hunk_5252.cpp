                ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                  NULL, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                ctx->stream.avail_out = c->bufferSize;

                {
                    unsigned long compCRC, compLen;
                    compCRC = getLong(buf);
                    if (ctx->crc != compCRC) {
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01394)
                                      "Zlib: CRC error inflating data");
                        return APR_EGENERAL;
                    }
                    compLen = getLong(buf + VALIDATION_SIZE / 2);
                    /* gzip stores original size only as 4 byte value */
                    if ((ctx->stream.total_out & 0xFFFFFFFF) != compLen) {
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01395)
                                      "Zlib: Length %ld of inflated data does "
                                      "not match expected value %ld",
                                      ctx->stream.total_out, compLen);
                        return APR_EGENERAL;
                    }
                }

                inflateEnd(&ctx->stream);

                ctx->done = 1;

                /* Did we have trailing data behind the closing 8 bytes? */
                if (avail > valid) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02485)
                                  "Encountered extra data after compressed data");
                    return APR_EGENERAL;
                }
            }

