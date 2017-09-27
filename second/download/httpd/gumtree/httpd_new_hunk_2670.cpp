                    memcpy(ctx->validation_buffer, ctx->stream.next_in,
                           ctx->validation_buffer_length);
                break;
            }

            if (zRC != Z_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01409)
                              "Zlib error %d inflating data (%s)", zRC,
                              ctx->stream.msg);
                return APR_EGENERAL;
            }
        }

        apr_bucket_delete(e);
    }
