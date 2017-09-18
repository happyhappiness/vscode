	*temp = '\0';              /* overlay it with the null terminator */

    r->status_line = apr_pstrdup(r->pool, urlbuff);            /* Save status line into request rec  */

    apr_file_close(dobj->hfd);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Served headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}

static apr_status_t read_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb) 
{
