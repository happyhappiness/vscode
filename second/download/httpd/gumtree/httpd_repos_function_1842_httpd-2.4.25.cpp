static int ap_set_byterange(request_rec *r, apr_off_t clength,
                            apr_array_header_t **indexes,
                            int *overlaps, int *reversals)
{
    const char *range;
    const char *ct;
    char *cur;
    apr_array_header_t *merged;
    int num_ranges = 0, unsatisfiable = 0;
    apr_off_t ostart = 0, oend = 0, sum_lengths = 0;
    int in_merge = 0;
    indexes_t *idx;
    int ranges = 1;
    int i;
    const char *it;

    *overlaps = 0;
    *reversals = 0;

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
     */
    if (AP_CONDITION_NOMATCH == ap_condition_if_range(r, r->headers_out)) {
        return 0;
    }

    range += 6;
    it = range;
    while (*it) {
        if (*it++ == ',') {
            ranges++;
        }
    }
    it = range;
    if (ranges > MAX_PREALLOC_RANGES) {
        ranges = MAX_PREALLOC_RANGES;
    }
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
                /*
                 * special case: 0-
                 *   ignore all other ranges provided
                 *   return as a single range: 0-
                 */
                if (start == 0) {
                    num_ranges = 0;
                    sum_lengths = 0;
                    in_merge = 1;
                    oend = end;
                    ostart = start;
                    apr_array_clear(*indexes);
                    break;
                }
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

        if (!in_merge) {
 