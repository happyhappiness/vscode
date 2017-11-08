static int file_cache_handler(request_rec *r)
{
    a_file *match;
    int errstatus;
    int rc = OK;

    /* XXX: not sure if this is right yet
     * see comment in http_core.c:default_handler
     */
    if (ap_strcmp_match(r->handler, "*/*")) {
        return DECLINED;
    }

    /* we don't handle anything but GET */
    if (r->method_number != M_GET) return DECLINED;

    /* did xlat phase find the file? */
    match = ap_get_module_config(r->request_config, &file_cache_module);

    if (match == NULL) {
        return DECLINED;
    }

    /* note that we would handle GET on this resource */
    r->allowed |= (AP_METHOD_BIT << M_GET);

    /* This handler has no use for a request body (yet), but we still
     * need to read and discard it if the client sent one.
     */
    if ((errstatus = ap_discard_request_body(r)) != OK)
        return errstatus;

    ap_update_mtime(r, match->finfo.mtime);

    /* ap_set_last_modified() always converts the file mtime to a string
     * which is slow.  Accelerate the common case.
     * ap_set_last_modified(r);
     */
    {
        apr_time_t mod_time;
        char *datestr;

        mod_time = ap_rationalize_mtime(r, r->mtime);
        if (mod_time == match->finfo.mtime)
            datestr = match->mtimestr;
        else {
            datestr = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
            apr_rfc822_date(datestr, mod_time);
        }
        apr_table_setn(r->headers_out, "Last-Modified", datestr);
    }

    /* ap_set_content_length() always converts the same number and never
     * returns an error.  Accelerate it.
     */
    r->clength = match->finfo.size;
    apr_table_setn(r->headers_out, "Content-Length", match->sizestr);

    ap_set_etag(r);
    if ((errstatus = ap_meets_conditions(r)) != OK) {
       return errstatus;
    }

    /* Call appropriate handler */
    if (!r->header_only) {
        if (match->is_mmapped == TRUE)
            rc = mmap_handler(r, match);
        else
            rc = sendfile_handler(r, match);
    }

    return rc;
}