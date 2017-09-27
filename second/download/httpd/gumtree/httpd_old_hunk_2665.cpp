             * large enough output buffer to put ALL data in otherwise it
             * fails, whereas in the deflate case you can empty a filled output
             * buffer and call it again until no more output can be created.
             */
            flush_libz_buffer(ctx, c, f->c->bucket_alloc, inflate, Z_SYNC_FLUSH,
                              UPDATE_CRC);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Zlib: Inflated %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);

            if (ctx->validation_buffer_length == VALIDATION_SIZE) {
                unsigned long compCRC, compLen;
                compCRC = getLong(ctx->validation_buffer);
                if (ctx->crc != compCRC) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Zlib: Checksum of inflated stream invalid");
                    return APR_EGENERAL;
                }
                ctx->validation_buffer += VALIDATION_SIZE / 2;
                compLen = getLong(ctx->validation_buffer);
                if (ctx->stream.total_out != compLen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Zlib: Length of inflated stream invalid");
                    return APR_EGENERAL;
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Zlib: Validation bytes not present");
                return APR_EGENERAL;
            }

            inflateEnd(&ctx->stream);
            /* No need for cleanup any longer */
