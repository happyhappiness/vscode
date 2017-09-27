         apr_array_header_t* varray;
         apr_time_t expire;
 
         len = sizeof(expire);
         apr_file_read_full(dobj->hfd, &expire, len, &len);
 
-        if (expire < r->request_time) {
-            return DECLINED;
-        }
-
         varray = apr_array_make(r->pool, 5, sizeof(char*));
         rc = read_array(r, varray, dobj->hfd);
         if (rc != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                          "disk_cache: Cannot parse vary header file: %s",
                          dobj->hdrsfile);
