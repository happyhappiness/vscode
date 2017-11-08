int dav_get_depth(request_rec *r, int def_depth)
{
    const char *depth = apr_table_get(r->headers_in, "Depth");

    if (depth == NULL) {
        return def_depth;
    }

    if (strcasecmp(depth, "infinity") == 0) {
        return DAV_INFINITY;
    }
    else if (strcmp(depth, "0") == 0) {
        return 0;
    }
    else if (strcmp(depth, "1") == 0) {
        return 1;
    }

    /* The caller will return an HTTP_BAD_REQUEST. This will augment the
     * default message that Apache provides. */
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "An invalid Depth header was specified.");
    return -1;
}