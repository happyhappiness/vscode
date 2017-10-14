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
            if (apr_strtoff(&number, dash+1, &errp, 10) || *errp) {
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
            if (apr_strtoff(&number, cur, &errp, 10) || *errp) {
                return 0;
            }
            start = number;
            if (*dash) {
                if (apr_strtoff(&number, dash, &errp, 10) || *errp) {
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