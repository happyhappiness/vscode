static int dav_parse_range(request_rec *r,
                           apr_off_t *range_start, apr_off_t *range_end)
{
    const char *range_c;
    char *range;
    char *dash;
    char *slash;
    char *errp;

    range_c = apr_table_get(r->headers_in, "content-range");
    if (range_c == NULL)
        return 0;

    range = apr_pstrdup(r->pool, range_c);
    if (strncasecmp(range, "bytes ", 6) != 0
        || (dash = ap_strchr(range, '-')) == NULL
        || (slash = ap_strchr(range, '/')) == NULL) {
        /* malformed header. ignore it (per S14.16 of RFC2616) */
        return 0;
    }

    *dash++ = *slash++ = '\0';

    /* ignore invalid ranges. (per S14.16 of RFC2616) */
    if (apr_strtoff(range_start, range + 6, &errp, 10)
        || *errp || *range_start < 0) {
        return 0;
    }

    if (apr_strtoff(range_end, dash, &errp, 10)
        || *errp || *range_end < 0 || *range_end < *range_start) {
        return 0;
    }

    if (*slash != '*') {
        apr_off_t dummy;

        if (apr_strtoff(&dummy, slash, &errp, 10)
            || *errp || dummy <= *range_end) {
            return 0;
        }
    }

    /* we now have a valid range */
    return 1;
}