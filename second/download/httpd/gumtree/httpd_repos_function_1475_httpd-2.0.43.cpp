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