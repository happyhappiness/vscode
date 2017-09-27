                /* Is the remaining 8 bytes already in the avail stream? */
                if (ctx->stream.avail_in >= 8) {
                    unsigned long compCRC, compLen;
                    compCRC = getLong(ctx->stream.next_in);
                    if (ctx->crc != compCRC) {
                        inflateEnd(&ctx->stream);
                        return APR_EGENERAL;
                    }
                    ctx->stream.next_in += 4;
                    compLen = getLong(ctx->stream.next_in);
                    if (ctx->stream.total_out != compLen) {
                        inflateEnd(&ctx->stream);
                        return APR_EGENERAL;
                    }
                }
                else {
                    /* FIXME: We need to grab the 8 verification bytes
                     * from the wire! */
                    inflateEnd(&ctx->stream);
                    return APR_EGENERAL;
                }

                inflateEnd(&ctx->stream);

                eos = apr_bucket_eos_create(f->c->bucket_alloc);
