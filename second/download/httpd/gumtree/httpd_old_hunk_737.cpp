AP_DECLARE(void) ap_clear_method_list(ap_method_list_t *l)
{
    l->method_mask = 0;
    l->method_list->nelts = 0;
}

/* Generate the human-readable hex representation of an unsigned long
 * (basically a faster version of 'sprintf("%lx")')
 */
#define HEX_DIGITS "0123456789abcdef"
static char *etag_ulong_to_hex(char *next, unsigned long u)
{
    int printing = 0;
    int shift = sizeof(unsigned long) * 8 - 4;
    do {
        unsigned long next_digit = ((u >> shift) & (unsigned long)0xf);
        if (next_digit) {
            *next++ = HEX_DIGITS[next_digit];
            printing = 1;
        }
        else if (printing) {
            *next++ = HEX_DIGITS[next_digit];
        }
        shift -= 4;
    } while (shift);
    *next++ = HEX_DIGITS[u & (unsigned long)0xf];
    return next;
}

#define ETAG_WEAK "W/"
#define CHARS_PER_UNSIGNED_LONG (sizeof(unsigned long) * 2)
/*
 * Construct an entity tag (ETag) from resource information.  If it's a real
 * file, build in some of the file characteristics.  If the modification time
 * is newer than (request-time minus 1 second), mark the ETag as weak - it
 * could be modified again in as short an interval.  We rationalize the
 * modification time we're given to keep it from being in the future.
 */
AP_DECLARE(char *) ap_make_etag(request_rec *r, int force_weak)
{
    char *weak;
    apr_size_t weak_len;
    char *etag;
    char *next;
    core_dir_config *cfg;
    etag_components_t etag_bits;
    etag_components_t bits_added;

    cfg = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                  &core_module);
    etag_bits = (cfg->etag_bits & (~ cfg->etag_remove)) | cfg->etag_add;
    
    /*
     * If it's a file (or we wouldn't be here) and no ETags
     * should be set for files, return an empty string and
     * note it for the header-sender to ignore.
     */
    if (etag_bits & ETAG_NONE) {
        apr_table_setn(r->notes, "no-etag", "omit");
        return "";
    }

    if (etag_bits == ETAG_UNSET) {
        etag_bits = ETAG_BACKWARD;
    }
    /*
     * Make an ETag header out of various pieces of information. We use
     * the last-modified date and, if we have a real file, the
     * length and inode number - note that this doesn't have to match
     * the content-length (i.e. includes), it just has to be unique
     * for the file.
     *
     * If the request was made within a second of the last-modified date,
     * we send a weak tag instead of a strong one, since it could
     * be modified again later in the second, and the validation
     * would be incorrect.
     */
    if ((r->request_time - r->mtime > (1 * APR_USEC_PER_SEC)) &&
        !force_weak) {
        weak = NULL;
        weak_len = 0;
    }
    else {
        weak = ETAG_WEAK;
        weak_len = sizeof(ETAG_WEAK);
    }

    if (r->finfo.filetype != 0) {
        /*
         * ETag gets set to [W/]"inode-size-mtime", modulo any
         * FileETag keywords.
         */
        etag = apr_palloc(r->pool, weak_len + sizeof("\"--\"") +
                          3 * CHARS_PER_UNSIGNED_LONG + 1);
        next = etag;
        if (weak) {
            while (*weak) {
                *next++ = *weak++;
            }
        }
        *next++ = '"';
        bits_added = 0;
        if (etag_bits & ETAG_INODE) {
            next = etag_ulong_to_hex(next, (unsigned long)r->finfo.inode);
            bits_added |= ETAG_INODE;
        }
        if (etag_bits & ETAG_SIZE) {
            if (bits_added != 0) {
                *next++ = '-';
            }
            next = etag_ulong_to_hex(next, (unsigned long)r->finfo.size);
            bits_added |= ETAG_SIZE;
        }
        if (etag_bits & ETAG_MTIME) {
            if (bits_added != 0) {
                *next++ = '-';
            }
            next = etag_ulong_to_hex(next, (unsigned long)r->mtime);
        }
        *next++ = '"';
        *next = '\0';
    }
    else {
        /*
         * Not a file document, so just use the mtime: [W/]"mtime"
         */
        etag = apr_palloc(r->pool, weak_len + sizeof("\"\"") +
                          CHARS_PER_UNSIGNED_LONG + 1);
        next = etag;
        if (weak) {
            while (*weak) {
                *next++ = *weak++;
            }
        }
        *next++ = '"';
        next = etag_ulong_to_hex(next, (unsigned long)r->mtime);
        *next++ = '"';
        *next = '\0';
    }

    return etag;
}

AP_DECLARE(void) ap_set_etag(request_rec *r)
{
    char *etag;
    char *variant_etag, *vlv;
    int vlv_weak;

    if (!r->vlist_validator) {
        etag = ap_make_etag(r, 0);
    
        /* If we get a blank etag back, don't set the header. */
        if (!etag[0]) {
            return;
        }
    }
    else {
        /* If we have a variant list validator (vlv) due to the
         * response being negotiated, then we create a structured
         * entity tag which merges the variant etag with the variant
         * list validator (vlv).  This merging makes revalidation
         * somewhat safer, ensures that caches which can deal with
         * Vary will (eventually) be updated if the set of variants is
         * changed, and is also a protocol requirement for transparent
         * content negotiation.
         */

        /* if the variant list validator is weak, we make the whole
         * structured etag weak.  If we would not, then clients could
         * have problems merging range responses if we have different
         * variants with the same non-globally-unique strong etag.
         */

        vlv = r->vlist_validator;
        vlv_weak = (vlv[0] == 'W');

        variant_etag = ap_make_etag(r, vlv_weak);

        /* If we get a blank etag back, don't append vlv and stop now. */
        if (!variant_etag[0]) {
            return;
        }

        /* merge variant_etag and vlv into a structured etag */
        variant_etag[strlen(variant_etag) - 1] = '\0';
        if (vlv_weak) {
            vlv += 3;
        }
        else {
            vlv++;
        }
        etag = apr_pstrcat(r->pool, variant_etag, ";", vlv, NULL);
    }

    apr_table_setn(r->headers_out, "ETag", etag);
}

static int ap_set_byterange(request_rec *r, apr_off_t clength,
                            apr_array_header_t **indexes);

/*
 * Here we try to be compatible with clients that want multipart/x-byteranges
 * instead of multipart/byteranges (also see above), as per HTTP/1.1. We
 * look for the Request-Range header (e.g. Netscape 2 and 3) as an indication
 * that the browser supports an older protocol. We also check User-Agent
 * for Microsoft Internet Explorer 3, which needs this as well.
 */
static int use_range_x(request_rec *r)
{
    const char *ua;
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

typedef struct indexes_t {
    apr_off_t start;
    apr_off_t end;
} indexes_t;

static int get_max_ranges(request_rec *r) {
    core_dir_config *core_conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                                         &core_module);
    if (core_conf->max_ranges >= 0 || core_conf->max_ranges == AP_MAXRANGES_UNLIMITED) {
        return core_conf->max_ranges;
    }

    /* Any other negative val means the default */
    return AP_DEFAULT_MAX_RANGES;
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
    char *boundary = NULL;
    char *bound_head = NULL;
    apr_array_header_t *indexes;
    indexes_t *idx;
    int original_status;
    int max_ranges = get_max_ranges(r);
    int i;

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
    num_ranges = ap_set_byterange(r, clength, &indexes);

    /* We have nothing to do, get out of the way. */
    if (num_ranges == 0 || (max_ranges >= 0 && num_ranges > max_ranges)) {
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
        boundary = apr_psprintf(r->pool, "%" APR_UINT64_T_HEX_FMT "%lx",
                                (apr_uint64_t)r->request_time, c->id);

        ap_set_content_type(r, apr_pstrcat(r->pool, "multipart",
                                           use_range_x(r) ? "/x-" : "/",
                                           "byteranges; boundary=",
                                           boundary, NULL));

        bound_head = apr_pstrcat(r->pool,
                                 CRLF "--", boundary,
                                 CRLF "Content-type: ",
                                 orig_ct,
                                 CRLF "Content-range: bytes ",
                                 NULL);
        ap_xlate_proto_to_ascii(bound_head, strlen(bound_head));
    }

    tmpbb = apr_brigade_create(r->pool, c->bucket_alloc);

    idx = (indexes_t *)indexes->elts;
    for (i = 0; i < indexes->nelts; i++, idx++) {
        range_start = idx->start;
        range_end = idx->end;

        rv = copy_brigade_range(bb, tmpbb, range_start, range_end);
        if (rv != APR_SUCCESS ) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
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
        end = apr_pstrcat(r->pool, CRLF "--", boundary, "--" CRLF, NULL);
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

/* for consistency with 2.2 code which uses apr_strtoff()
 * (missing from apr 0.9)
 */
static apr_status_t strtoff(apr_off_t *offset, const char *nptr,
                           char **endptr, int base)
{
   errno = 0;
   if (sizeof(apr_off_t) == 4) {
       *offset = strtol(nptr, endptr, base);
   }
   else {
       *offset = apr_strtoi64(nptr, endptr, base);
   }
   return APR_FROM_OS_ERROR(errno);
}

static int ap_set_byterange(request_rec *r, apr_off_t clength,
                            apr_array_header_t **indexes)
{
    const char *range;
    const char *if_range;
    const char *match;
    const char *ct;
    char *cur;
    int num_ranges = 0, unsatisfiable = 0;
    apr_off_t sum_lengths = 0;
    indexes_t *idx;
    int ranges = 1;
    const char *it;

    if (r->assbackwards) {
        return 0;
    }

    /*
     * Check for Range request-header (HTTP/1.1) or Request-Range for
     * backwards-compatibility with second-draft Luotonen/Franks
     * byte-ranges (e.g. Netscape Navigator 2-3).
     *
     * We support this form, with Request-Range, and (farther down) we
     * send multipart/x-byteranges instead of multipart/byteranges for
     * Request-Range based requests to work around a bug in Netscape
     * Navigator 2-3 and MSIE 3.
     */

    if (!(range = apr_table_get(r->headers_in, "Range"))) {
        range = apr_table_get(r->headers_in, "Request-Range");
    }

    if (!range || strncasecmp(range, "bytes=", 6) || r->status != HTTP_OK) {
        return 0;
    }

    /* is content already a single range? */
    if (apr_table_get(r->headers_out, "Content-Range")) {
       return 0;
    }

    /* is content already a multiple range? */
    if ((ct = apr_table_get(r->headers_out, "Content-Type"))
        && (!strncasecmp(ct, "multipart/byteranges", 20)
            || !strncasecmp(ct, "multipart/x-byteranges", 22))) {
       return 0;
    }

    /*
     * Check the If-Range header for Etag or Date.
     * Note that this check will return false (as required) if either
     * of the two etags are weak.
     */
    if ((if_range = apr_table_get(r->headers_in, "If-Range"))) {
        if (if_range[0] == '"') {
            if (!(match = apr_table_get(r->headers_out, "Etag"))
                || (strcmp(if_range, match) != 0)) {
                return 0;
            }
        }
        else if (!(match = apr_table_get(r->headers_out, "Last-Modified"))
                 || (strcmp(if_range, match) != 0)) {
            return 0;
        }
    }

    range += 6;
    it = range;
    while (*it) {
        if (*it++ == ',') {
            ranges++;
        }
    }
    it = range;
    *indexes = apr_array_make(r->pool, ranges, sizeof(indexes_t));
    while ((cur = ap_getword(r->pool, &range, ','))) {
        char *dash;
        char *errp;
        apr_off_t number, start, end;

        if (!*cur)
            break;

        /*
         * Per RFC 2616 14.35.1: If there is at least one syntactically invalid
         * byte-range-spec, we must ignore the whole header.
         */

        if (!(dash = strchr(cur, '-'))) {
            return 0;
        }

        if (dash == cur) {
            /* In the form "-5" */
            if (strtoff(&number, dash+1, &errp, 10) || *errp) {
                return 0;
            }
            if (number < 1) {
                return 0;
            }
            start = clength - number;
            end = clength - 1;
        }
        else {
            *dash++ = '\0';
            if (strtoff(&number, cur, &errp, 10) || *errp) {
                return 0;
            }
            start = number;
            if (*dash) {
                if (strtoff(&number, dash, &errp, 10) || *errp) {
                    return 0;
                }
                end = number;
                if (start > end) {
                    return 0;
                }
            }
            else {                  /* "5-" */
                end = clength - 1;
            }
        }

        if (start < 0) {
            start = 0;
        }
        if (start >= clength) {
            unsatisfiable = 1;
            continue;
        }
        if (end >= clength) {
            end = clength - 1;
        }

        idx = (indexes_t *)apr_array_push(*indexes);
        idx->start = start;
        idx->end = end;
        sum_lengths += end - start + 1;
        /* new set again */
        num_ranges++;
    }

    if (num_ranges == 0 && unsatisfiable) {
        /* If all ranges are unsatisfiable, we should return 416 */
        return -1;
    }
    if (sum_lengths >= clength) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Sum of ranges not smaller than file, ignoring.");
        return 0;
    }

    r->status = HTTP_PARTIAL_CONTENT;
    r->range = it;

    return num_ranges;
}
