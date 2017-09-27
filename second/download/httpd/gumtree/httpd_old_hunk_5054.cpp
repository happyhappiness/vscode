                ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                  NULL, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                ctx->stream.avail_out = c->bufferSize;

                /* Is the remaining 8 bytes already in the avail stream? */
                if (ctx->stream.avail_in >= 8) {
                    unsigned long compCRC, compLen;
                    compCRC = getLong(ctx->stream.next_in);
                    if (ctx->crc != compCRC) {
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01394)
                                      "Zlib: CRC error inflating data");
