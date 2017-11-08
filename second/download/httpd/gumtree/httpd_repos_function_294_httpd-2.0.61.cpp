static int dav_parse_range(request_rec *r,
                           apr_off_t *range_start, apr_off_t *range_end)
{
    const char *range_c;
    char *range;
    char *dash;
    char *slash;

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

    *dash = *slash = '\0';

    *range_start = apr_atoi64(range + 6);
    *range_end = apr_atoi64(dash + 1);

    if (*range_end < *range_start
        || (slash[1] != '*' && apr_atoi64(slash + 1) <= *range_end)) {
        /* invalid range. ignore it (per S14.16 of RFC2616) */
        return 0;
    }

    /* we now have a valid range */
    return 1;
}