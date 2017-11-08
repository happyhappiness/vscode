static int file_cache_write_mydata(apr_file_t *fd , cache_handle_t *h, request_rec *r)
{
    apr_status_t rc;
    char *buf;
    apr_size_t amt;

    char	dateHexS[sizeof(apr_time_t) * 2 + 1];
    char	expireHexS[sizeof(apr_time_t) * 2 + 1];
    char	verHexS[sizeof(apr_time_t) * 2 + 1];
    char	requestHexS[sizeof(apr_time_t) * 2 + 1];
    char	responseHexS[sizeof(apr_time_t) * 2 + 1];
    cache_info *info = &(h->cache_obj->info);
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    
    if (!r->headers_out) {
        /* XXX log message */
        return 0;
    }

    ap_cache_usec2hex(info->date, dateHexS);
    ap_cache_usec2hex(info->expire, expireHexS);
    ap_cache_usec2hex(dobj->version++, verHexS);
    ap_cache_usec2hex(info->request_time, requestHexS);
    ap_cache_usec2hex(info->response_time, responseHexS);
    buf = apr_pstrcat(r->pool, dateHexS, " ", expireHexS, " ", verHexS, " ", requestHexS, " ", responseHexS, "\n", NULL);
    amt = strlen(buf);
    rc = apr_file_write(fd, buf, &amt);
    if (rc != APR_SUCCESS) {
        /* XXX log message */
        return 0;
    }

    buf = apr_pstrcat(r->pool, "X-NAME: ", dobj->name, "\n", NULL);
    amt = strlen(buf);
    rc = apr_file_write(fd, buf, &amt);
    if (rc != APR_SUCCESS) {
        /* XXX log message */
        return 0;
    }
    return 1;
}