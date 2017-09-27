                    memcpy(ctx->validation_buffer, ctx->stream.next_in,
                           ctx->validation_buffer_length);
                break;
            }

            if (zRC != Z_OK) {
                return APR_EGENERAL;
            }
        }

        apr_bucket_delete(e);
    }
