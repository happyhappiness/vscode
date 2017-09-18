        if (rv != APR_SUCCESS) {
            /* XXX log */
        }

        apr_file_close(dobj->fd);
        dobj->fd = NULL;
        /* XXX log */
    }

    return APR_SUCCESS;
}

static apr_status_t file_cache_errorcleanup(disk_cache_object_t *dobj, request_rec *r)
{
    if (dobj->fd) {
        apr_file_close(dobj->fd);
        dobj->fd = NULL;
    }
    /* Remove the header file, the temporary body file, and a potential old body file */
    apr_file_remove(dobj->hdrsfile, r->pool);
    apr_file_remove(dobj->tempfile, r->pool);
    apr_file_remove(dobj->datafile, r->pool);

    /* Return non-APR_SUCCESS in order to have mod_cache remove the disk_cache filter */
    return DECLINED;
}


/* These two functions get and put state information into the data
 * file for an ap_cache_el, this state information will be read
 * and written transparent to clients of this module
 */
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

/*
 * Hook and mod_cache callback functions
 */
#define AP_TEMPFILE "/aptmpXXXXXX"
static int create_entity(cache_handle_t *h, request_rec *r,
                         const char *key,
                         apr_off_t len)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);
    apr_status_t rv;
    cache_object_t *obj;
    disk_cache_object_t *dobj;
    apr_file_t *tmpfile;

    if (conf->cache_root == NULL) {
        return DECLINED;
    }

    /* If the Content-Length is still unknown, cache anyway */
    if (len != -1 && (len < conf->minfs || len > conf->maxfs)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check, "
                     "or is incomplete",
                     key);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    obj = apr_pcalloc(r->pool, sizeof(*obj));
