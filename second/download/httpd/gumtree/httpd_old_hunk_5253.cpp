                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01399)
                                  "Zlib: Checksum of inflated stream invalid");
                    return APR_EGENERAL;
                }
                ctx->validation_buffer += VALIDATION_SIZE / 2;
                compLen = getLong(ctx->validation_buffer);
                if (ctx->stream.total_out != compLen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01400)
                                  "Zlib: Length of inflated stream invalid");
                    return APR_EGENERAL;
                }
            }
            else {
