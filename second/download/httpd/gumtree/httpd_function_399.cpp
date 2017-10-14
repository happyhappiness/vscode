static int file_cache_recall_mydata(apr_file_t *fd, cache_info *info,
                                    disk_cache_object_t *dobj, request_rec *r)
{
    apr_status_t rv;
    char *urlbuff;
    disk_cache_info_t disk_info;
    apr_size_t len;

    /* read the data from the cache file */
    len = sizeof(disk_cache_info_t);
    rv = apr_file_read_full(fd, &disk_info, len, &len);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (disk_info.format != DISK_FORMAT_VERSION) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: URL %s had a on-disk version mismatch",
                     r->uri);
        return APR_EGENERAL;
    }

    /* Store it away so we can get it later. */
    dobj->disk_info = disk_info;

    info->date = disk_info.date;
    info->expire = disk_info.expire;
    info->request_time = disk_info.request_time;
    info->response_time = disk_info.response_time;

    /* Note that we could optimize this by conditionally doing the palloc
     * depending upon the size. */
    urlbuff = apr_palloc(r->pool, disk_info.name_len + 1);
    len = disk_info.name_len;
    rv = apr_file_read_full(fd, urlbuff, len, &len);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    urlbuff[disk_info.name_len] = '\0';

    /* check that we have the same URL */
    /* Would strncmp be correct? */
    if (strcmp(urlbuff, dobj->name) != 0) {
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}