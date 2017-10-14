apr_status_t ap_http_filter(ap_filter_t *f, apr_bucket_brigade *b,
                            ap_input_mode_t mode, apr_read_type_e block,
                            apr_off_t readbytes)
{
    apr_bucket *e;
    http_ctx_t *ctx = f->ctx;
    apr_status_t rv;
    apr_off_t totalread;
    int http_error = HTTP_REQUEST_ENTITY_TOO_LARGE;
    apr_bucket_brigade *bb;

    /* just get out of the way of things we don't want. */
    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE) {
        return ap_get_brigade(f->next, b, mode, block, readbytes);
    }

    if (!ctx) {
        const char *tenc, *lenp;
        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
        ctx->state = BODY_NONE;
        ctx->pos = ctx->chunk_ln;
        ctx->bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        bb = ctx->bb;

        /* LimitRequestBody does not apply to proxied responses.
         * Consider implementing this check in its own filter.
         * Would adding a directive to limit the size of proxied
         * responses be useful?
         */
        if (!f->r->proxyreq) {
            ctx->limit = ap_get_limit_req_body(f->r);
        }
        else {
            ctx->limit = 0;
        }

        tenc = apr_table_get(f->r->headers_in, "Transfer-Encoding");
        lenp = apr_table_get(f->r->headers_in, "Content-Length");

        if (tenc) {
            if (!strcasecmp(tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
            /* test lenp, because it gives another case we can handle */
            else if (!lenp) {
                /* Something that isn't in HTTP, unless some future
                 * edition defines new transfer ecodings, is unsupported.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Unknown Transfer-Encoding: %s", tenc);
                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r,
                  "Unknown Transfer-Encoding: %s; using Content-Length", tenc);
                tenc = NULL;
            }
        }
        if (lenp && !tenc) {
            char *endstr;

            ctx->state = BODY_LENGTH;

            /* Protects against over/underflow, non-digit chars in the
             * string (excluding leading space) (the endstr checks)
             * and a negative number. */
            if (apr_strtoff(&ctx->remaining, lenp, &endstr, 10)
                || endstr == lenp || *endstr || ctx->remaining < 0) {

                ctx->remaining = 0;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }

            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid.
             */
            if (ctx->limit && ctx->limit < ctx->remaining) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                          "Requested content-length of %" APR_OFF_T_FMT
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->remaining, ctx->limit);
                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }
        }

        /* If we don't have a request entity indicated by the headers, EOS.
         * (BODY_NONE is a valid intermediate state due to trailers,
         *  but it isn't a valid starting state.)
         *
         * RFC 2616 Section 4.4 note 5 states that connection-close
         * is invalid for a request entity - request bodies must be
         * denoted by C-L or T-E: chunked.
         *
         * Note that since the proxy uses this filter to handle the
         * proxied *response*, proxy responses MUST be exempt.
         */
        if (ctx->state == BODY_NONE && f->r->proxyreq != PROXYREQ_RESPONSE) {
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(b, e);
            ctx->eos_sent = 1;
            return APR_SUCCESS;
        }

        /* Since we're about to read data, send 100-Continue if needed.
         * Only valid on chunked and C-L bodies where the C-L is > 0. */
        if ((ctx->state == BODY_CHUNK ||
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