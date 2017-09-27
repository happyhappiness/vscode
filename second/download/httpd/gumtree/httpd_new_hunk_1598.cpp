    return (apr_table_get(r->headers_in, "Request-Range")
            || ((ua = apr_table_get(r->headers_in, "User-Agent"))
                && ap_strstr_c(ua, "MSIE 3")));
}

#define BYTERANGE_FMT "%" APR_OFF_T_FMT "-%" APR_OFF_T_FMT "/%" APR_OFF_T_FMT
#define PARTITION_ERR_FMT "apr_brigade_partition() failed " \
                          "[%" APR_OFF_T_FMT ",%" APR_OFF_T_FMT "]"

AP_CORE_DECLARE_NONSTD(apr_status_t) ap_byterange_filter(ap_filter_t *f,
                                                         apr_bucket_brigade *bb)
{
#define MIN_LENGTH(len1, len2) ((len1 > len2) ? len2 : len1)
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    byterange_ctx *ctx;
    apr_bucket *e;
    apr_bucket_brigade *bsend;
    apr_off_t range_start;
    apr_off_t range_end;
    char *current;
    apr_off_t clength = 0;
    apr_status_t rv;
    int found = 0;
    int num_ranges;

    /* Iterate through the brigade until reaching EOS or a bucket with
     * unknown length. */
    for (e = APR_BRIGADE_FIRST(bb);
         (e != APR_BRIGADE_SENTINEL(bb) && !APR_BUCKET_IS_EOS(e)
          && e->length != (apr_size_t)-1);
         e = APR_BUCKET_NEXT(e)) {
        clength += e->length;
    }

    /* Don't attempt to do byte range work if this brigade doesn't
     * contain an EOS, or if any of the buckets has an unknown length;
     * this avoids the cases where it is expensive to perform
     * byteranging (i.e. may require arbitrary amounts of memory). */
    if (!APR_BUCKET_IS_EOS(e) || clength <= 0) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    num_ranges = ap_set_byterange(r);

    /* We have nothing to do, get out of the way. */
    if (num_ranges == 0) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    ctx = apr_pcalloc(r->pool, sizeof(*ctx));
    ctx->num_ranges = num_ranges;
    /* create a brigade in case we never call ap_save_brigade() */
    ctx->bb = apr_brigade_create(r->pool, c->bucket_alloc);

    if (ctx->num_ranges > 1) {
        /* Is ap_make_content_type required here? */
        const char *orig_ct = ap_make_content_type(r, r->content_type);
        ctx->boundary = apr_psprintf(r->pool, "%" APR_UINT64_T_HEX_FMT "%lx",
                                     (apr_uint64_t)r->request_time, (long) getpid());

        ap_set_content_type(r, apr_pstrcat(r->pool, "multipart",
                                           use_range_x(r) ? "/x-" : "/",
                                           "byteranges; boundary=",
                                           ctx->boundary, NULL));

        if (orig_ct) {
            ctx->bound_head = apr_pstrcat(r->pool,
                                          CRLF "--", ctx->boundary,
                                          CRLF "Content-type: ",
                                          orig_ct,
                                          CRLF "Content-range: bytes ",
                                          NULL);
        }
        else {
            /* if we have no type for the content, do our best */
            ctx->bound_head = apr_pstrcat(r->pool,
                                          CRLF "--", ctx->boundary,
                                          CRLF "Content-range: bytes ",
                                          NULL);
        }
        ap_xlate_proto_to_ascii(ctx->bound_head, strlen(ctx->bound_head));
    }

    /* this brigade holds what we will be sending */
    bsend = apr_brigade_create(r->pool, c->bucket_alloc);

    while ((current = ap_getword(r->pool, &r->range, ','))
           && (rv = parse_byterange(current, clength, &range_start,
                                    &range_end))) {
        apr_bucket *e2;
        apr_bucket *ec;

        if (rv == -1) {
            continue;
        }

        /* These calls to apr_brigage_partition should only fail in
         * pathological cases, e.g. a file being truncated whilst
         * being served. */
        if ((rv = apr_brigade_partition(bb, range_start, &ec)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          PARTITION_ERR_FMT, range_start, clength);
            continue;
        }
        if ((rv = apr_brigade_partition(bb, range_end+1, &e2)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          PARTITION_ERR_FMT, range_end+1, clength);
            continue;
        }

        found = 1;

        /* For single range requests, we must produce Content-Range header.
         * Otherwise, we need to produce the multipart boundaries.
         */
        if (ctx->num_ranges == 1) {
            apr_table_setn(r->headers_out, "Content-Range",
                           apr_psprintf(r->pool, "bytes " BYTERANGE_FMT,
                                        range_start, range_end, clength));
        }
        else {
            char *ts;

            e = apr_bucket_pool_create(ctx->bound_head, strlen(ctx->bound_head),
                                       r->pool, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bsend, e);

            ts = apr_psprintf(r->pool, BYTERANGE_FMT CRLF CRLF,
                              range_start, range_end, clength);
            ap_xlate_proto_to_ascii(ts, strlen(ts));
            e = apr_bucket_pool_create(ts, strlen(ts), r->pool,
                                       c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bsend, e);
        }

        do {
            apr_bucket *foo;
            const char *str;
            apr_size_t len;

            if (apr_bucket_copy(ec, &foo) != APR_SUCCESS) {
                /* As above; this should not fail since the bucket has
                 * a known length, but just to be sure, this takes
                 * care of uncopyable buckets that do somehow manage
                 * to slip through.  */
                /* XXX: check for failure? */
                apr_bucket_read(ec, &str, &len, APR_BLOCK_READ);
                apr_bucket_copy(ec, &foo);
            }
            APR_BRIGADE_INSERT_TAIL(bsend, foo);
            ec = APR_BUCKET_NEXT(ec);
        } while (ec != e2);
    }

    if (found == 0) {
        ap_remove_output_filter(f);
        r->status = HTTP_OK;
        /* bsend is assumed to be empty if we get here. */
        e = ap_bucket_error_create(HTTP_RANGE_NOT_SATISFIABLE, NULL,
                                   r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bsend, e);
        e = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bsend, e);
        return ap_pass_brigade(f->next, bsend);
    }

    if (ctx->num_ranges > 1) {
        char *end;

        /* add the final boundary */
        end = apr_pstrcat(r->pool, CRLF "--", ctx->boundary, "--" CRLF, NULL);
        ap_xlate_proto_to_ascii(end, strlen(end));
        e = apr_bucket_pool_create(end, strlen(end), r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bsend, e);
    }

    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bsend, e);

    /* we're done with the original content - all of our data is in bsend. */
    apr_brigade_cleanup(bb);

    /* send our multipart output */
    return ap_pass_brigade(f->next, bsend);
}

static int ap_set_byterange(request_rec *r)
{
    const char *range;
    const char *if_range;
    const char *match;
    const char *ct;
    int num_ranges;

    if (r->assbackwards) {
        return 0;
    }

    /* Check for Range request-header (HTTP/1.1) or Request-Range for
     * backwards-compatibility with second-draft Luotonen/Franks
     * byte-ranges (e.g. Netscape Navigator 2-3).
     *
     * We support this form, with Request-Range, and (farther down) we
     * send multipart/x-byteranges instead of multipart/byteranges for
     * Request-Range based requests to work around a bug in Netscape
