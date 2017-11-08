static apr_status_t read_headers(cache_handle_t *h, request_rec *r) 
{
    apr_status_t rv;
    char urlbuff[1034];
    int urllen = sizeof(urlbuff);
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    apr_table_t * tmp;

    /* This case should not happen... */
    if (!dobj->fd || !dobj->hfd) {
        /* XXX log message */
        return APR_NOTFOUND; 
    }

    if(!r->headers_out) {
        r->headers_out = apr_table_make(r->pool, 20);
    }
    
    /*
     * Call routine to read the header lines/status line 
     */
    ap_scan_script_header_err(r, dobj->hfd, NULL);
 
    apr_table_setn(r->headers_out, "Content-Type", 
                   ap_make_content_type(r, r->content_type));

    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);           /* Read status  */
    if (rv != APR_SUCCESS) {
        /* XXX log message */
	return rv;
    }

    r->status = atoi(urlbuff);                           /* Save status line into request rec  */

    /* Read and ignore the status line (This request might result in a
     * 304, so we don't necessarily want to retransmit a 200 from the cache.)
     */
    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);
    if (rv != APR_SUCCESS) {
        /* XXX log message */
	return rv;
    }

    h->req_hdrs = apr_table_make(r->pool, 20);
    
    /*
     * Call routine to read the header lines/status line 
     */
    tmp = r->err_headers_out;
    r->err_headers_out = h->req_hdrs;
    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);           /* Read status  */
    ap_scan_script_header_err(r, dobj->hfd, NULL);
    r->err_headers_out = tmp;
 
    apr_file_close(dobj->hfd);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Served headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}