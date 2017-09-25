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
