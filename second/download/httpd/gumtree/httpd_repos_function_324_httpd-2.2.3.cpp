static int dav_get_overwrite(request_rec *r)
{
    const char *overwrite = apr_table_get(r->headers_in, "Overwrite");

    if (overwrite == NULL) {
        return 1; /* default is "T" */
    }

    if ((*overwrite == 'F' || *overwrite == 'f') && overwrite[1] == '\0') {
        return 0;
    }

    if ((*overwrite == 'T' || *overwrite == 't') && overwrite[1] == '\0') {
        return 1;
    }

    /* The caller will return an HTTP_BAD_REQUEST. This will augment the
     * default message that Apache provides. */
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "An invalid Overwrite header was specified.");
    return -1;
}