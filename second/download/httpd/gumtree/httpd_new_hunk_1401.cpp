                }
            }

            zRC = deflate(&(ctx->stream), Z_NO_FLUSH);

            if (zRC != Z_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Zlib error %d deflating data (%s)", zRC,
                              ctx->stream.msg);
                return APR_EGENERAL;
            }
        }

        apr_bucket_delete(e);
    }

    apr_brigade_cleanup(bb);
    return APR_SUCCESS;
}

static apr_status_t consume_zlib_flags(deflate_ctx *ctx,
                                       const char **data, apr_size_t *len)
{
    if ((ctx->zlib_flags & EXTRA_FIELD)) {
        /* Consume 2 bytes length prefixed data. */
        if (ctx->consume_pos == 0) {
            if (!*len) {
                return APR_INCOMPLETE;
            }
            ctx->consume_len = (unsigned int)**data;
            ctx->consume_pos++;
            ++*data;
            --*len;
        }
        if (ctx->consume_pos == 1) {
            if (!*len) {
                return APR_INCOMPLETE;
            }
            ctx->consume_len += ((unsigned int)**data) << 8;
            ctx->consume_pos++;
            ++*data;
            --*len;
        }
        if (*len < ctx->consume_len) {
            ctx->consume_len -= *len;
            *len = 0;
            return APR_INCOMPLETE;
        }
        *data += ctx->consume_len;
        *len -= ctx->consume_len;

        ctx->consume_len = ctx->consume_pos = 0;
        ctx->zlib_flags &= ~EXTRA_FIELD;
    }

    if ((ctx->zlib_flags & ORIG_NAME)) {
        /* Consume nul terminated string. */
        while (*len && **data) {
            ++*data;
            --*len;
        }
        if (!*len) {
            return APR_INCOMPLETE;
        }
        /* .. and nul. */
        ++*data;
        --*len;

        ctx->zlib_flags &= ~ORIG_NAME;
    }

    if ((ctx->zlib_flags & COMMENT)) {
        /* Consume nul terminated string. */
        while (*len && **data) {
            ++*data;
            --*len;
        }
        if (!*len) {
            return APR_INCOMPLETE;
        }
        /* .. and nul. */
        ++*data;
        --*len;

        ctx->zlib_flags &= ~COMMENT;
    }

    if ((ctx->zlib_flags & HEAD_CRC)) {
        /* Consume CRC16 (2 octets). */
        if (ctx->consume_pos == 0) {
            if (!*len) {
                return APR_INCOMPLETE;
            }
            ctx->consume_pos++;
            ++*data;
            --*len;
        }
        if (!*len) {
            return APR_INCOMPLETE;
        }
        ++*data;
        --*len;
        
        ctx->consume_pos = 0;
        ctx->zlib_flags &= ~HEAD_CRC;
    }

    return APR_SUCCESS;
}

/* This is the deflate input filter (inflates).  */
static apr_status_t deflate_in_filter(ap_filter_t *f,
                                      apr_bucket_brigade *bb,
                                      ap_input_mode_t mode,
                                      apr_read_type_e block,
                                      apr_off_t readbytes)
