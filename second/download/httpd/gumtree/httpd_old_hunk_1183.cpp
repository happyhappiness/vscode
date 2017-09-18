        if (rv != APR_SUCCESS) {
            /* XXX log */
        }

        apr_file_close(dobj->fd);
        dobj->fd = NULL;
       /* XXX log */
   }

   return APR_SUCCESS;
}


/* These two functions get and put state information into the data 
 * file for an ap_cache_el, this state information will be read 
 * and written transparent to clients of this module 
 */
static int file_cache_read_mydata(apr_file_t *fd, cache_info *info, 
                                  disk_cache_object_t *dobj)
{
    apr_status_t rv;
    char urlbuff[1034]; /* XXX FIXME... THIS IS A POTENTIAL SECURITY HOLE */
    int urllen = sizeof(urlbuff);
    int offset=0;
    char * temp;

    /* read the data from the cache file */
    /* format
     * date SP expire SP count CRLF
     * dates are stored as a hex representation of apr_time_t (number of
     * microseconds since 00:00:00 january 1, 1970 UTC)
     */
    rv = apr_file_gets(&urlbuff[0], urllen, fd);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if ((temp = strchr(&urlbuff[0], '\n')) != NULL) /* trim off new line character */
        *temp = '\0';      /* overlay it with the null terminator */

    if (!apr_date_checkmask(urlbuff, "&&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&&")) {
        return APR_EGENERAL;
    }

    info->date = ap_cache_hex2usec(urlbuff + offset);
    offset += (sizeof(info->date)*2) + 1;
    info->expire = ap_cache_hex2usec(urlbuff + offset);
    offset += (sizeof(info->expire)*2) + 1;
    dobj->version = ap_cache_hex2usec(urlbuff + offset);
    offset += (sizeof(info->expire)*2) + 1;
    info->request_time = ap_cache_hex2usec(urlbuff + offset);
    offset += (sizeof(info->expire)*2) + 1;
    info->response_time = ap_cache_hex2usec(urlbuff + offset);
    
    /* check that we have the same URL */
    rv = apr_file_gets(&urlbuff[0], urllen, fd);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if ((temp = strchr(&urlbuff[0], '\n')) != NULL) { /* trim off new line character */
        *temp = '\0';      /* overlay it with the null terminator */
    }

    if (strncmp(urlbuff, "X-NAME: ", 7) != 0) {
        return APR_EGENERAL;
    }
    if (strcmp(urlbuff + 8, dobj->name) != 0) {
        return APR_EGENERAL;
    }
    
    return APR_SUCCESS;
}

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

/*
 * Hook and mod_cache callback functions
 */
#define AP_TEMPFILE "/aptmpXXXXXX"
static int create_entity(cache_handle_t *h, request_rec *r,
                         const char *type, 
                         const char *key, 
                         apr_off_t len)
{ 
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config, 
                                                 &disk_cache_module);
    apr_status_t rv;
    cache_object_t *obj;
    disk_cache_object_t *dobj;
    apr_file_t *tmpfile;

    if (strcasecmp(type, "disk")) {
        return DECLINED;
    }

    if (conf->cache_root == NULL) {
        return DECLINED;
    }

    if (len < conf->minfs || len > conf->maxfs) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check, "
                     "or is incomplete", 
                     key);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    obj = apr_pcalloc(r->pool, sizeof(*obj));
