            (ctx->state == BODY_LENGTH && ctx->remaining > 0)) &&
            f->r->expecting_100 && f->r->proto_num >= HTTP_VERSION(1,1) &&
            !(f->r->eos_sent || f->r->bytes_sent)) {
            if (!ap_is_HTTP_SUCCESS(f->r->status)) {
                ctx->state = BODY_NONE;
                ctx->eos_sent = 1;
            } else {
                char *tmp;
                int len;

                /* if we send an interim response, we're no longer
                 * in a state of expecting one.
                 */
                f->r->expecting_100 = 0;
                tmp = apr_pstrcat(f->r->pool, AP_SERVER_PROTOCOL, " ",
                                  ap_get_status_line(HTTP_CONTINUE), CRLF CRLF,
                                  NULL);
                len = strlen(tmp);
                ap_xlate_proto_to_ascii(tmp, len);
                apr_brigade_cleanup(bb);
                e = apr_bucket_pool_create(tmp, len, f->r->pool,
                                           f->c->bucket_alloc);
                APR_BRIGADE_INSERT_HEAD(bb, e);
                e = apr_bucket_flush_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);

                ap_pass_brigade(f->c->output_filters, bb);
            }
        }

        /* We can't read the chunk until after sending 100 if required. */
        if (ctx->state == BODY_CHUNK) {
            apr_brigade_cleanup(bb);

            rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
                                block, 0);

            /* for timeout */
            if (block == APR_NONBLOCK_READ &&
                ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
                  (APR_STATUS_IS_EAGAIN(rv)) )) {
                ctx->state = BODY_CHUNK_PART;
                return APR_EAGAIN;
            }

            if (rv == APR_SUCCESS) {
                rv = get_chunk_line(ctx, bb, f->r->server->limit_req_line);
                if (APR_STATUS_IS_EAGAIN(rv)) {
                    apr_brigade_cleanup(bb);
                    ctx->state = BODY_CHUNK_PART;
                    return rv;
                }
                if (rv == APR_SUCCESS) {
                    ctx->remaining = get_chunk_size(ctx->chunk_ln);
                    if (ctx->remaining == INVALID_CHAR) {
                        rv = APR_EGENERAL;
                        http_error = HTTP_SERVICE_UNAVAILABLE;
                    }
                }
            }
            apr_brigade_cleanup(bb);

            /* Detect chunksize error (such as overflow) */
            if (rv != APR_SUCCESS || ctx->remaining < 0) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading first chunk %s ", 
                              (ctx->remaining < 0) ? "(overflow)" : "");
                ctx->remaining = 0; /* Reset it in case we have to
                                     * come back here later */
                if (APR_STATUS_IS_TIMEUP(rv)) { 
                    http_error = HTTP_REQUEST_TIME_OUT;
                }
                return bail_out_on_error(ctx, f, http_error);
            }

            if (!ctx->remaining) {
                /* Handle trailers by calling ap_get_mime_headers again! */
                ctx->state = BODY_NONE;
                ap_get_mime_headers(f->r);
                e = apr_bucket_eos_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(b, e);
                ctx->eos_sent = 1;
                return APR_SUCCESS;
            }
        }
    }
    else {
        bb = ctx->bb;
    }

    if (ctx->eos_sent) {
        e = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(b, e);
        return APR_SUCCESS;
    }

    if (!ctx->remaining) {
        switch (ctx->state) {
        case BODY_NONE:
            break;
        case BODY_LENGTH:
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(b, e);
            ctx->eos_sent = 1;
            return APR_SUCCESS;
        case BODY_CHUNK:
        case BODY_CHUNK_PART:
            {
                apr_brigade_cleanup(bb);

                /* We need to read the CRLF after the chunk.  */
                if (ctx->state == BODY_CHUNK) {
                    rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
                                        block, 0);
                    if (block == APR_NONBLOCK_READ &&
                        ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
                          (APR_STATUS_IS_EAGAIN(rv)) )) {
                        return APR_EAGAIN;
                    }
                    /* If we get an error, then leave */
                    if (rv != APR_SUCCESS) {
                        return rv;
                    }
                    /*
                     * We really don't care whats on this line. If it is RFC
                     * compliant it should be only \r\n. If there is more
                     * before we just ignore it as long as we do not get over
                     * the limit for request lines.
                     */
                    rv = get_remaining_chunk_line(ctx, bb,
                                                  f->r->server->limit_req_line);
                    apr_brigade_cleanup(bb);
                    if (APR_STATUS_IS_EAGAIN(rv)) {
                        return rv;
                    }
                } else {
                    rv = APR_SUCCESS;
                }

                if (rv == APR_SUCCESS) {
                    /* Read the real chunk line. */
                    rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
                                        block, 0);
                    /* Test timeout */
                    if (block == APR_NONBLOCK_READ &&
                        ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
                          (APR_STATUS_IS_EAGAIN(rv)) )) {
                        ctx->state = BODY_CHUNK_PART;
                        return APR_EAGAIN;
                    }
                    ctx->state = BODY_CHUNK;
                    if (rv == APR_SUCCESS) {
                        rv = get_chunk_line(ctx, bb, f->r->server->limit_req_line);
                        if (APR_STATUS_IS_EAGAIN(rv)) {
                            ctx->state = BODY_CHUNK_PART;
                            apr_brigade_cleanup(bb);
                            return rv;
                        }
                        if (rv == APR_SUCCESS) {
                            ctx->remaining = get_chunk_size(ctx->chunk_ln);
                            if (ctx->remaining == INVALID_CHAR) {
                                rv = APR_EGENERAL;
                                http_error = HTTP_SERVICE_UNAVAILABLE;
                            }
                        }
                    }
                    apr_brigade_cleanup(bb);
                }

                /* Detect chunksize error (such as overflow) */
                if (rv != APR_SUCCESS || ctx->remaining < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading chunk %s ", 
                                  (ctx->remaining < 0) ? "(overflow)" : "");
                    ctx->remaining = 0; /* Reset it in case we have to
                                         * come back here later */
                    if (APR_STATUS_IS_TIMEUP(rv)) { 
                        http_error = HTTP_REQUEST_TIME_OUT;
                    }
                    return bail_out_on_error(ctx, f, http_error);
                }

                if (!ctx->remaining) {
                    /* Handle trailers by calling ap_get_mime_headers again! */
                    ctx->state = BODY_NONE;
                    ap_get_mime_headers(f->r);
                    e = apr_bucket_eos_create(f->c->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(b, e);
                    ctx->eos_sent = 1;
                    return APR_SUCCESS;
                }
            }
            break;
        }
    }

    /* Ensure that the caller can not go over our boundary point. */
    if (ctx->state == BODY_LENGTH || ctx->state == BODY_CHUNK) {
        if (ctx->remaining < readbytes) {
            readbytes = ctx->remaining;
        }
        AP_DEBUG_ASSERT(readbytes > 0);
    }

    rv = ap_get_brigade(f->next, b, mode, block, readbytes);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* How many bytes did we just read? */
    apr_brigade_length(b, 0, &totalread);

    /* If this happens, we have a bucket of unknown length.  Die because
     * it means our assumptions have changed. */
    AP_DEBUG_ASSERT(totalread >= 0);

    if (ctx->state != BODY_NONE) {
        ctx->remaining -= totalread;
        if (ctx->remaining > 0) {
            e = APR_BRIGADE_LAST(b);
            if (APR_BUCKET_IS_EOS(e))
                return APR_EOF;
        }
    }

    /* If we have no more bytes remaining on a C-L request,
     * save the callter a roundtrip to discover EOS.
     */
    if (ctx->state == BODY_LENGTH && ctx->remaining == 0) {
        e = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(b, e);
    }

    /* We have a limit in effect. */
    if (ctx->limit) {
        /* FIXME: Note that we might get slightly confused on chunked inputs
         * as we'd need to compensate for the chunk lengths which may not
         * really count.  This seems to be up for interpretation.  */
        ctx->limit_used += totalread;
        if (ctx->limit < ctx->limit_used) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                          "Read content-length of %" APR_OFF_T_FMT
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->limit_used, ctx->limit);
            apr_brigade_cleanup(bb);
            e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
                                       f->r->pool,
                                       f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            ctx->eos_sent = 1;
            return ap_pass_brigade(f->r->output_filters, bb);
        }
    }

    return APR_SUCCESS;
}

/**
 * Parse a chunk extension, detect overflow.
 * There are two error cases:
 *  1) If the conversion would require too many bits, a -1 is returned.
 *  2) If the conversion used the correct number of bits, but an overflow
 *     caused only the sign bit to flip, then that negative number is
 *     returned.
 * In general, any negative number can be considered an overflow error.
 */
static long get_chunk_size(char *b)
{
    long chunksize = 0;
    size_t chunkbits = sizeof(long) * 8;

    ap_xlate_proto_from_ascii(b, strlen(b));

    if (!apr_isxdigit(*b)) {
        /*
         * Detect invalid character at beginning. This also works for empty
         * chunk size lines.
         */
        return INVALID_CHAR;
    }
    /* Skip leading zeros */
    while (*b == '0') {
        ++b;
    }

    while (apr_isxdigit(*b) && (chunkbits > 0)) {
        int xvalue = 0;

        if (*b >= '0' && *b <= '9') {
            xvalue = *b - '0';
        }
        else if (*b >= 'A' && *b <= 'F') {
            xvalue = *b - 'A' + 0xa;
        }
        else if (*b >= 'a' && *b <= 'f') {
            xvalue = *b - 'a' + 0xa;
        }

        chunksize = (chunksize << 4) | xvalue;
        chunkbits -= 4;
        ++b;
    }
    if (apr_isxdigit(*b) && (chunkbits <= 0)) {
        /* overflow */
        return -1;
    }

    return chunksize;
}

typedef struct header_struct {
    apr_pool_t *pool;
    apr_bucket_brigade *bb;
} header_struct;

/* Send a single HTTP header field to the client.  Note that this function
 * is used in calls to table_do(), so their interfaces are co-dependent.
 * In other words, don't change this one without checking table_do in alloc.c.
 * It returns true unless there was a write error of some kind.
 */
static int form_header_field(header_struct *h,
                             const char *fieldname, const char *fieldval)
{
#if APR_CHARSET_EBCDIC
