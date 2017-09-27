 * @@@: XXX: FIXME: currently the headers are passed thru un-merged.
 * Is that okay, or should they be collapsed where possible?
 */
static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
{
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    apr_status_t rv;

    /* This case should not happen... */
    if (!dobj->hdrs.fd) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00719)
                "recalling headers; but no header fd for %s", dobj->name);
        return APR_NOTFOUND;
    }

    h->req_hdrs = apr_table_make(r->pool, 20);
    h->resp_hdrs = apr_table_make(r->pool, 20);

    /* Call routine to read the header lines/status line */
    rv = read_table(h, r, h->resp_hdrs, dobj->hdrs.fd);
    if (rv != APR_SUCCESS) { 
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02987) 
                      "Error reading response headers from %s for %s",
                      dobj->hdrs.file, dobj->name);
    }
    rv = read_table(h, r, h->req_hdrs, dobj->hdrs.fd);
    if (rv != APR_SUCCESS) { 
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02988) 
                      "Error reading request headers from %s for %s",
                      dobj->hdrs.file, dobj->name);
    }

    apr_file_close(dobj->hdrs.fd);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00720)
            "Recalled headers for URL %s", dobj->name);
    return APR_SUCCESS;
