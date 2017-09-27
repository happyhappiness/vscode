
    /* Just remove the filter, if it doesn't work the first time, it won't
     * work at all for this request.
     */
    ap_remove_output_filter(f);

    if (!r) {
        /*
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02131)
                     "Unable to get upgradeable socket handle");
        */
        return ap_pass_brigade(f->next, bb);
    }

    /* No need to ensure that this is a server with optional SSL, the filter
     * is only inserted if that is true.
     */

    upgrade = apr_table_get(r->headers_in, "Upgrade");
    if (upgrade == NULL
