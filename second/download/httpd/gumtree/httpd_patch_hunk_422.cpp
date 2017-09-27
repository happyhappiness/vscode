         if (rv != APR_SUCCESS) {
             /* XXX log */
         }
 
         apr_file_close(dobj->fd);
         dobj->fd = NULL;
-       /* XXX log */
-   }
+        /* XXX log */
+    }
 
-   return APR_SUCCESS;
+    return APR_SUCCESS;
 }
 
+static apr_status_t file_cache_errorcleanup(disk_cache_object_t *dobj, request_rec *r)
+{
+    if (dobj->fd) {
+        apr_file_close(dobj->fd);
+        dobj->fd = NULL;
+    }
+    /* Remove the header file, the temporary body file, and a potential old body file */
+    apr_file_remove(dobj->hdrsfile, r->pool);
+    apr_file_remove(dobj->tempfile, r->pool);
+    apr_file_remove(dobj->datafile, r->pool);
+
+    /* Return non-APR_SUCCESS in order to have mod_cache remove the disk_cache filter */
+    return DECLINED;
+}
 
-/* These two functions get and put state information into the data 
- * file for an ap_cache_el, this state information will be read 
- * and written transparent to clients of this module 
+
+/* These two functions get and put state information into the data
+ * file for an ap_cache_el, this state information will be read
+ * and written transparent to clients of this module
  */
-static int file_cache_read_mydata(apr_file_t *fd, cache_info *info, 
-                                  disk_cache_object_t *dobj)
+static int file_cache_recall_mydata(apr_file_t *fd, cache_info *info,
+                                    disk_cache_object_t *dobj, request_rec *r)
 {
     apr_status_t rv;
-    char urlbuff[1034]; /* XXX FIXME... THIS IS A POTENTIAL SECURITY HOLE */
-    int urllen = sizeof(urlbuff);
-    int offset=0;
-    char * temp;
+    char *urlbuff;
+    disk_cache_info_t disk_info;
+    apr_size_t len;
 
     /* read the data from the cache file */
-    /* format
-     * date SP expire SP count CRLF
-     * dates are stored as a hex representation of apr_time_t (number of
-     * microseconds since 00:00:00 january 1, 1970 UTC)
-     */
-    rv = apr_file_gets(&urlbuff[0], urllen, fd);
+    len = sizeof(disk_cache_info_t);
+    rv = apr_file_read_full(fd, &disk_info, len, &len);
     if (rv != APR_SUCCESS) {
         return rv;
     }
 
-    if ((temp = strchr(&urlbuff[0], '\n')) != NULL) /* trim off new line character */
-        *temp = '\0';      /* overlay it with the null terminator */
-
-    if (!apr_date_checkmask(urlbuff, "&&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&& &&&&&&&&&&&&&&&&")) {
+    if (disk_info.format != DISK_FORMAT_VERSION) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                     "cache_disk: URL %s had a on-disk version mismatch",
+                     r->uri);
         return APR_EGENERAL;
     }
 
-    info->date = ap_cache_hex2usec(urlbuff + offset);
-    offset += (sizeof(info->date)*2) + 1;
-    info->expire = ap_cache_hex2usec(urlbuff + offset);
-    offset += (sizeof(info->expire)*2) + 1;
-    dobj->version = ap_cache_hex2usec(urlbuff + offset);
-    offset += (sizeof(info->expire)*2) + 1;
-    info->request_time = ap_cache_hex2usec(urlbuff + offset);
-    offset += (sizeof(info->expire)*2) + 1;
-    info->response_time = ap_cache_hex2usec(urlbuff + offset);
-    
-    /* check that we have the same URL */
-    rv = apr_file_gets(&urlbuff[0], urllen, fd);
+    /* Store it away so we can get it later. */
+    dobj->disk_info = disk_info;
+
+    info->date = disk_info.date;
+    info->expire = disk_info.expire;
+    info->request_time = disk_info.request_time;
+    info->response_time = disk_info.response_time;
+
+    /* Note that we could optimize this by conditionally doing the palloc
+     * depending upon the size. */
+    urlbuff = apr_palloc(r->pool, disk_info.name_len + 1);
+    len = disk_info.name_len;
+    rv = apr_file_read_full(fd, urlbuff, len, &len);
     if (rv != APR_SUCCESS) {
         return rv;
     }
+    urlbuff[disk_info.name_len] = '\0';
 
-    if ((temp = strchr(&urlbuff[0], '\n')) != NULL) { /* trim off new line character */
-        *temp = '\0';      /* overlay it with the null terminator */
-    }
-
-    if (strncmp(urlbuff, "X-NAME: ", 7) != 0) {
-        return APR_EGENERAL;
-    }
-    if (strcmp(urlbuff + 8, dobj->name) != 0) {
+    /* check that we have the same URL */
+    /* Would strncmp be correct? */
+    if (strcmp(urlbuff, dobj->name) != 0) {
         return APR_EGENERAL;
     }
-    
-    return APR_SUCCESS;
-}
-
-static int file_cache_write_mydata(apr_file_t *fd , cache_handle_t *h, request_rec *r)
-{
-    apr_status_t rc;
-    char *buf;
-    apr_size_t amt;
-
-    char	dateHexS[sizeof(apr_time_t) * 2 + 1];
-    char	expireHexS[sizeof(apr_time_t) * 2 + 1];
-    char	verHexS[sizeof(apr_time_t) * 2 + 1];
-    char	requestHexS[sizeof(apr_time_t) * 2 + 1];
-    char	responseHexS[sizeof(apr_time_t) * 2 + 1];
-    cache_info *info = &(h->cache_obj->info);
-    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
-    
-    if (!r->headers_out) {
-        /* XXX log message */
-        return 0;
-    }
 
-    ap_cache_usec2hex(info->date, dateHexS);
-    ap_cache_usec2hex(info->expire, expireHexS);
-    ap_cache_usec2hex(dobj->version++, verHexS);
-    ap_cache_usec2hex(info->request_time, requestHexS);
-    ap_cache_usec2hex(info->response_time, responseHexS);
-    buf = apr_pstrcat(r->pool, dateHexS, " ", expireHexS, " ", verHexS, " ", requestHexS, " ", responseHexS, "\n", NULL);
-    amt = strlen(buf);
-    rc = apr_file_write(fd, buf, &amt);
-    if (rc != APR_SUCCESS) {
-        /* XXX log message */
-        return 0;
-    }
-
-    buf = apr_pstrcat(r->pool, "X-NAME: ", dobj->name, "\n", NULL);
-    amt = strlen(buf);
-    rc = apr_file_write(fd, buf, &amt);
-    if (rc != APR_SUCCESS) {
-        /* XXX log message */
-        return 0;
-    }
-    return 1;
+    return APR_SUCCESS;
 }
 
 /*
  * Hook and mod_cache callback functions
  */
 #define AP_TEMPFILE "/aptmpXXXXXX"
 static int create_entity(cache_handle_t *h, request_rec *r,
-                         const char *type, 
-                         const char *key, 
+                         const char *key,
                          apr_off_t len)
-{ 
-    disk_cache_conf *conf = ap_get_module_config(r->server->module_config, 
+{
+    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                  &disk_cache_module);
     apr_status_t rv;
     cache_object_t *obj;
     disk_cache_object_t *dobj;
     apr_file_t *tmpfile;
 
-    if (strcasecmp(type, "disk")) {
-        return DECLINED;
-    }
-
     if (conf->cache_root == NULL) {
         return DECLINED;
     }
 
-    if (len < conf->minfs || len > conf->maxfs) {
+    /* If the Content-Length is still unknown, cache anyway */
+    if (len != -1 && (len < conf->minfs || len > conf->maxfs)) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "cache_disk: URL %s failed the size check, "
-                     "or is incomplete", 
+                     "or is incomplete",
                      key);
         return DECLINED;
     }
 
     /* Allocate and initialize cache_object_t and disk_cache_object_t */
     obj = apr_pcalloc(r->pool, sizeof(*obj));
