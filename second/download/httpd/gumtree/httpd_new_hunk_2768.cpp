    return (apr_table_get(r->headers_in, "Request-Range")
            || ((ua = apr_table_get(r->headers_in, "User-Agent"))
                && ap_strstr_c(ua, "MSIE 3")));
}

#define BYTERANGE_FMT "%" APR_OFF_T_FMT "-%" APR_OFF_T_FMT "/%" APR_OFF_T_FMT

static apr_status_t copy_brigade_range(apr_bucket_brigade *bb,
                                       apr_bucket_brigade *bbout,
                                       apr_off_t start,
                                       apr_off_t end)
{
    apr_bucket *first = NULL, *last = NULL, *out_first = NULL, *e;
    apr_uint64_t pos = 0, off_first = 0, off_last = 0;
    apr_status_t rv;
    apr_uint64_t start64, end64;
    apr_off_t pofft = 0;

    /*
     * Once we know that start and end are >= 0 convert everything to apr_uint64_t.
     * See the comments in apr_brigade_partition why.
     * In short apr_off_t (for values >= 0)and apr_size_t fit into apr_uint64_t.
     */
    start64 = (apr_uint64_t)start;
    end64 = (apr_uint64_t)end;

    if (start < 0 || end < 0 || start64 > end64)
        return APR_EINVAL;

    for (e = APR_BRIGADE_FIRST(bb);
         e != APR_BRIGADE_SENTINEL(bb);
         e = APR_BUCKET_NEXT(e))
    {
        apr_uint64_t elen64;
        /* we know that no bucket has undefined length (-1) */
        AP_DEBUG_ASSERT(e->length != (apr_size_t)(-1));
        elen64 = (apr_uint64_t)e->length;
        if (!first && (elen64 + pos > start64)) {
            first = e;
            off_first = pos;
        }
        if (elen64 + pos > end64) {
            last = e;
            off_last = pos;
            break;
        }
        pos += elen64;
    }
    if (!first || !last)
        return APR_EINVAL;

    e = first;
    while (1)
    {
        apr_bucket *copy;
        AP_DEBUG_ASSERT(e != APR_BRIGADE_SENTINEL(bb));
        rv = apr_bucket_copy(e, &copy);
        if (rv != APR_SUCCESS) {
            apr_brigade_cleanup(bbout);
            return rv;
        }

        APR_BRIGADE_INSERT_TAIL(bbout, copy);
        if (e == first) {
            if (off_first != start64) {
                rv = apr_bucket_split(copy, (apr_size_t)(start64 - off_first));
                if (rv != APR_SUCCESS) {
                    apr_brigade_cleanup(bbout);
                    return rv;
                }
                out_first = APR_BUCKET_NEXT(copy);
                APR_BUCKET_REMOVE(copy);
                apr_bucket_destroy(copy);
            }
            else {
                out_first = copy;
            }
        }
        if (e == last) {
            if (e == first) {
                off_last += start64 - off_first;
                copy = out_first;
            }
            if (end64 - off_last != (apr_uint64_t)e->length) {
                rv = apr_bucket_split(copy, (apr_size_t)(end64 + 1 - off_last));
                if (rv != APR_SUCCESS) {
                    apr_brigade_cleanup(bbout);
                    return rv;
                }
                copy = APR_BUCKET_NEXT(copy);
                if (copy != APR_BRIGADE_SENTINEL(bbout)) {
                    APR_BUCKET_REMOVE(copy);
                    apr_bucket_destroy(copy);
                }
            }
            break;
        }
        e = APR_BUCKET_NEXT(e);
    }

    AP_DEBUG_ASSERT(APR_SUCCESS == apr_brigade_length(bbout, 1, &pofft));
    pos = (apr_uint64_t)pofft;
    AP_DEBUG_ASSERT(pos == end64 - start64 + 1);
    return APR_SUCCESS;
}

static apr_status_t send_416(ap_filter_t *f, apr_bucket_brigade *tmpbb)
{
    apr_bucket *e;
    conn_rec *c = f->r->connection;
    ap_remove_output_filter(f);
    f->r->status = HTTP_OK;
    e = ap_bucket_error_create(HTTP_RANGE_NOT_SATISFIABLE, NULL,
                               f->r->pool, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(tmpbb, e);
    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(tmpbb, e);
    return ap_pass_brigade(f->next, tmpbb);
}

AP_CORE_DECLARE_NONSTD(apr_status_t) ap_byterange_filter(ap_filter_t *f,
                                                         apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    apr_bucket *e;
    apr_bucket_brigade *bsend;
    apr_bucket_brigade *tmpbb;
    apr_off_t range_start;
    apr_off_t range_end;
    apr_off_t clength = 0;
    apr_status_t rv;
    int found = 0;
    int num_ranges;
    char *bound_head = NULL;
    apr_array_header_t *indexes;
    indexes_t *idx;
    int i;
    int original_status;
    int max_ranges, max_overlaps, max_reversals;
    int overlaps = 0, reversals = 0;
    core_dir_config *core_conf = ap_get_core_module_config(r->per_dir_config);

    max_ranges = ( (core_conf->max_ranges >= 0 || core_conf->max_ranges == AP_MAXRANGES_UNLIMITED)
                   ? core_conf->max_ranges
                   : AP_DEFAULT_MAX_RANGES );
    max_overlaps = ( (core_conf->max_overlaps >= 0 || core_conf->max_overlaps == AP_MAXRANGES_UNLIMITED)
                  ? core_conf->max_overlaps
                  : AP_DEFAULT_MAX_OVERLAPS );
    max_reversals = ( (core_conf->max_reversals >= 0 || core_conf->max_reversals == AP_MAXRANGES_UNLIMITED)
                  ? core_conf->max_reversals
                  : AP_DEFAULT_MAX_REVERSALS );
    /*
     * Iterate through the brigade until reaching EOS or a bucket with
     * unknown length.
     */
    for (e = APR_BRIGADE_FIRST(bb);
         (e != APR_BRIGADE_SENTINEL(bb) && !APR_BUCKET_IS_EOS(e)
          && e->length != (apr_size_t)-1);
         e = APR_BUCKET_NEXT(e)) {
        clength += e->length;
    }

    /*
     * Don't attempt to do byte range work if this brigade doesn't
     * contain an EOS, or if any of the buckets has an unknown length;
     * this avoids the cases where it is expensive to perform
     * byteranging (i.e. may require arbitrary amounts of memory).
     */
    if (!APR_BUCKET_IS_EOS(e) || clength <= 0) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    original_status = r->status;
    num_ranges = ap_set_byterange(r, clength, &indexes, &overlaps, &reversals);

    /* No Ranges or we hit a limit? We have nothing to do, get out of the way. */
    if (num_ranges == 0 ||
        (max_ranges >= 0 && num_ranges > max_ranges) ||
        (max_overlaps >= 0 && overlaps > max_overlaps) ||
        (max_reversals >= 0 && reversals > max_reversals)) {
        r->status = original_status;
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    /* this brigade holds what we will be sending */
    bsend = apr_brigade_create(r->pool, c->bucket_alloc);

    if (num_ranges < 0)
        return send_416(f, bsend);

    if (num_ranges > 1) {
        /* Is ap_make_content_type required here? */
        const char *orig_ct = ap_make_content_type(r, r->content_type);

        ap_set_content_type(r, apr_pstrcat(r->pool, "multipart",
                                           use_range_x(r) ? "/x-" : "/",
                                           "byteranges; boundary=",
                                           ap_multipart_boundary, NULL));

        if (orig_ct) {
            bound_head = apr_pstrcat(r->pool,
                                     CRLF "--", ap_multipart_boundary,
                                     CRLF "Content-type: ",
                                     orig_ct,
                                     CRLF "Content-range: bytes ",
                                     NULL);
        }
        else {
            /* if we have no type for the content, do our best */
            bound_head = apr_pstrcat(r->pool,
                                     CRLF "--", ap_multipart_boundary,
                                     CRLF "Content-range: bytes ",
                                     NULL);
        }
        ap_xlate_proto_to_ascii(bound_head, strlen(bound_head));
    }

    tmpbb = apr_brigade_create(r->pool, c->bucket_alloc);

    idx = (indexes_t *)indexes->elts;
    for (i = 0; i < indexes->nelts; i++, idx++) {
        range_start = idx->start;
        range_end = idx->end;

        rv = copy_brigade_range(bb, tmpbb, range_start, range_end);
        if (rv != APR_SUCCESS ) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01584)
                          "copy_brigade_range() failed [%" APR_OFF_T_FMT
                          "-%" APR_OFF_T_FMT ",%" APR_OFF_T_FMT "]",
                          range_start, range_end, clength);
            continue;
        }
        found = 1;

        /*
         * For single range requests, we must produce Content-Range header.
         * Otherwise, we need to produce the multipart boundaries.
         */
        if (num_ranges == 1) {
            apr_table_setn(r->headers_out, "Content-Range",
                           apr_psprintf(r->pool, "bytes " BYTERANGE_FMT,
                                        range_start, range_end, clength));
        }
        else {
            char *ts;

            e = apr_bucket_pool_create(bound_head, strlen(bound_head),
                                       r->pool, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bsend, e);

            ts = apr_psprintf(r->pool, BYTERANGE_FMT CRLF CRLF,
                              range_start, range_end, clength);
            ap_xlate_proto_to_ascii(ts, strlen(ts));
            e = apr_bucket_pool_create(ts, strlen(ts), r->pool,
                                       c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bsend, e);
        }

        APR_BRIGADE_CONCAT(bsend, tmpbb);
        if (i && !(i & 0x1F)) {
            /*
             * Every now and then, pass what we have down the filter chain.
             * In this case, the content-length filter cannot calculate and
             * set the content length and we must remove any Content-Length
             * header already present.
             */
            apr_table_unset(r->headers_out, "Content-Length");
            if ((rv = ap_pass_brigade(f->next, bsend)) != APR_SUCCESS)
                return rv;
            apr_brigade_cleanup(bsend);
        }
    }

    if (found == 0) {
        /* bsend is assumed to be empty if we get here. */
        return send_416(f, bsend);
    }

    if (num_ranges > 1) {
        char *end;

        /* add the final boundary */
        end = apr_pstrcat(r->pool, CRLF "--", ap_multipart_boundary, "--" CRLF,
                          NULL);
        ap_xlate_proto_to_ascii(end, strlen(end));
        e = apr_bucket_pool_create(end, strlen(end), r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bsend, e);
    }

    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bsend, e);

    /* we're done with the original content - all of our data is in bsend. */
    apr_brigade_cleanup(bb);
    apr_brigade_destroy(tmpbb);

    /* send our multipart output */
    return ap_pass_brigade(f->next, bsend);
}
