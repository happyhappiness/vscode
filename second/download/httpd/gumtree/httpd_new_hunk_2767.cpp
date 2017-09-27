#include <stdarg.h>
#endif
#if APR_HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifndef AP_DEFAULT_MAX_RANGES
#define AP_DEFAULT_MAX_RANGES 200
#endif
#ifndef AP_DEFAULT_MAX_OVERLAPS
#define AP_DEFAULT_MAX_OVERLAPS 20
#endif
#ifndef AP_DEFAULT_MAX_REVERSALS
#define AP_DEFAULT_MAX_REVERSALS 20
#endif

#define MAX_PREALLOC_RANGES 100

APLOG_USE_MODULE(http);

typedef struct indexes_t {
    apr_off_t start;
    apr_off_t end;
} indexes_t;

/*
 * Returns: number of ranges (merged) or -1 for no-good
 */
static int ap_set_byterange(request_rec *r, apr_off_t clength,
                            apr_array_header_t **indexes,
                            int *overlaps, int *reversals)
{
    const char *range;
    const char *if_range;
    const char *match;
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
            /* new set */
            ostart = start;
            oend = end;
            in_merge = 1;
            continue;
        }
        in_merge = 0;

        if (start >= ostart && end <= oend) {
            in_merge = 1;
        }

        if (start < ostart && end >= ostart-1) {
            ostart = start;
            ++*reversals;
            in_merge = 1;
        }
        if (end >= oend && start <= oend+1 ) {
            oend = end;
            in_merge = 1;
        }

        if (in_merge) {
            ++*overlaps;
            continue;
        } else {
            idx = (indexes_t *)apr_array_push(*indexes);
            idx->start = ostart;
            idx->end = oend;
            sum_lengths += oend - ostart + 1;
            /* new set again */
            in_merge = 1;
            ostart = start;
            oend = end;
            num_ranges++;
        }
    }

    if (in_merge) {
        idx = (indexes_t *)apr_array_push(*indexes);
        idx->start = ostart;
        idx->end = oend;
        sum_lengths += oend - ostart + 1;
        num_ranges++;
    }
    else if (num_ranges == 0 && unsatisfiable) {
        /* If all ranges are unsatisfiable, we should return 416 */
        return -1;
    }
    if (sum_lengths > clength) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                      "Sum of ranges larger than file, ignoring.");
        return 0;
    }

    /*
     * create the merged table now, now that we know we need it
     */
    merged = apr_array_make(r->pool, num_ranges, sizeof(char *));
    idx = (indexes_t *)(*indexes)->elts;
    for (i = 0; i < (*indexes)->nelts; i++, idx++) {
        char **new = (char **)apr_array_push(merged);
        *new = apr_psprintf(r->pool, "%" APR_OFF_T_FMT "-%" APR_OFF_T_FMT,
                            idx->start, idx->end);
    }

    r->status = HTTP_PARTIAL_CONTENT;
    r->range = apr_array_pstrcat(r->pool, merged, ',');
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01583)
                  "Range: %s | %s (%d : %d : %"APR_OFF_T_FMT")",
                  it, r->range, *overlaps, *reversals, clength);

    return num_ranges;
}

/*
 * Here we try to be compatible with clients that want multipart/x-byteranges
 * instead of multipart/byteranges (also see above), as per HTTP/1.1. We
 * look for the Request-Range header (e.g. Netscape 2 and 3) as an indication
 * that the browser supports an older protocol. We also check User-Agent
