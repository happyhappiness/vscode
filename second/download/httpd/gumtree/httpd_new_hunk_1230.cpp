    /* This case should not happen... */
    if (!dobj->hfd) {
        /* XXX log message */
        return APR_NOTFOUND;
    }

    h->req_hdrs = apr_table_make(r->pool, 20);
    h->resp_hdrs = apr_table_make(r->pool, 20);
    h->resp_err_hdrs = apr_table_make(r->pool, 20);

    /* Call routine to read the header lines/status line */
    read_table(h, r, h->resp_hdrs, dobj->hfd);
    read_table(h, r, h->req_hdrs, dobj->hfd);

    apr_file_close(dobj->hfd);

    h->status = dobj->disk_info.status;
    h->content_type = apr_table_get(h->resp_hdrs, "Content-Type");

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "disk_cache: Recalled headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}

static apr_status_t recall_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb)
