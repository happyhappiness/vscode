                e = apr_bucket_pool_create(tmp, len, f->r->pool,
                                           f->c->bucket_alloc);
                APR_BRIGADE_INSERT_HEAD(bb, e);
                e = apr_bucket_flush_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);

                rv = ap_pass_brigade(f->c->output_filters, bb);
                if (rv != APR_SUCCESS) {
                    return AP_FILTER_ERROR;
                }
            }
        }
    }

    /* sanity check in case we're read twice */
    if (ctx->eos_sent) {
        e = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(b, e);
        return APR_SUCCESS;
    }

    do {
        apr_brigade_cleanup(b);
        again = 0; /* until further notice */

        /* read and handle the brigade */
        switch (ctx->state) {
        case BODY_CHUNK:
        case BODY_CHUNK_PART:
        case BODY_CHUNK_EXT:
        case BODY_CHUNK_CR:
        case BODY_CHUNK_LF:
        case BODY_CHUNK_END:
        case BODY_CHUNK_END_LF: {

            rv = ap_get_brigade(f->next, b, AP_MODE_GETLINE, block, 0);

            /* for timeout */
            if (block == APR_NONBLOCK_READ
                    && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
                            || (APR_STATUS_IS_EAGAIN(rv)))) {
                return APR_EAGAIN;
            }

            if (rv == APR_EOF) {
                return APR_INCOMPLETE;
            }

            if (rv != APR_SUCCESS) {
                return rv;
            }

            e = APR_BRIGADE_FIRST(b);
            while (e != APR_BRIGADE_SENTINEL(b)) {
                const char *buffer;
                apr_size_t len;

                if (!APR_BUCKET_IS_METADATA(e)) {
                    int parsing = 0;

                    rv = apr_bucket_read(e, &buffer, &len, APR_BLOCK_READ);

                    if (rv == APR_SUCCESS) {
                        parsing = 1;
                        rv = parse_chunk_size(ctx, buffer, len,
                                f->r->server->limit_req_fieldsize);
                    }
                    if (rv != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r, APLOGNO(01590)
                                      "Error reading/parsing chunk %s ",
                                      (APR_ENOSPC == rv) ? "(overflow)" : "");
                        if (parsing) {
                            if (rv != APR_ENOSPC) {
                                http_error = HTTP_BAD_REQUEST;
                            }
                            return bail_out_on_error(ctx, f, http_error);
                        }
                        return rv;
                    }
                }

                apr_bucket_delete(e);
                e = APR_BRIGADE_FIRST(b);
            }
            again = 1; /* come around again */

            if (ctx->state == BODY_CHUNK_TRAILER) {
                /* Treat UNSET as DISABLE - trailers aren't merged by default */
                return read_chunked_trailers(ctx, f, b,
                            conf->merge_trailers == AP_MERGE_TRAILERS_ENABLE);
            }

            break;
        }
        case BODY_NONE:
        case BODY_LENGTH:
        case BODY_CHUNK_DATA: {

            /* Ensure that the caller can not go over our boundary point. */
            if (ctx->state != BODY_NONE && ctx->remaining < readbytes) {
                readbytes = ctx->remaining;
            }
            if (readbytes > 0) {
                apr_off_t totalread;

                rv = ap_get_brigade(f->next, b, mode, block, readbytes);

                /* for timeout */
                if (block == APR_NONBLOCK_READ
                        && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
                                || (APR_STATUS_IS_EAGAIN(rv)))) {
                    return APR_EAGAIN;
                }

                if (rv == APR_EOF && ctx->state != BODY_NONE
                        && ctx->remaining > 0) {
                    return APR_INCOMPLETE;
                }

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
                        if (APR_BUCKET_IS_EOS(e)) {
                            apr_bucket_delete(e);
                            return APR_INCOMPLETE;
                        }
                    }
                    else if (ctx->state == BODY_CHUNK_DATA) {
                        /* next chunk please */
                        ctx->state = BODY_CHUNK_END;
                        ctx->chunk_used = 0;
                    }
                }

                /* We have a limit in effect. */
                if (ctx->limit) {
                    /* FIXME: Note that we might get slightly confused on
                     * chunked inputs as we'd need to compensate for the chunk
                     * lengths which may not really count.  This seems to be up
                     * for interpretation.
                     */
                    ctx->limit_used += totalread;
                    if (ctx->limit < ctx->limit_used) {
                        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                                      APLOGNO(01591) "Read content length of "
                                      "%" APR_OFF_T_FMT " is larger than the "
                                      "configured limit of %" APR_OFF_T_FMT,
                                      ctx->limit_used, ctx->limit);
                        return bail_out_on_error(ctx, f,
                                                 HTTP_REQUEST_ENTITY_TOO_LARGE);
                    }
                }
            }

            /* If we have no more bytes remaining on a C-L request,
             * save the caller a round trip to discover EOS.
             */
            if (ctx->state == BODY_LENGTH && ctx->remaining == 0) {
                e = apr_bucket_eos_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(b, e);
                ctx->eos_sent = 1;
            }

            break;
        }
        case BODY_CHUNK_TRAILER: {

            rv = ap_get_brigade(f->next, b, mode, block, readbytes);

            /* for timeout */
            if (block == APR_NONBLOCK_READ
                    && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
                            || (APR_STATUS_IS_EAGAIN(rv)))) {
                return APR_EAGAIN;
            }

            if (rv != APR_SUCCESS) {
                return rv;
            }

            break;
        }
        default: {
            /* Should not happen */
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(02901)
                          "Unexpected body state (%i)", (int)ctx->state);
            return APR_EGENERAL;
        }
        }

    } while (again);

    return APR_SUCCESS;
}

typedef struct header_struct {
    apr_pool_t *pool;
    apr_bucket_brigade *bb;
} header_struct;
