 
     iov[0].iov_base = (void*)&disk_info;
     iov[0].iov_len = sizeof(disk_cache_info_t);
     iov[1].iov_base = (void*)dobj->name;
     iov[1].iov_len = disk_info.name_len;
 
-    rv = apr_file_writev(dobj->hdrs.tempfd, (const struct iovec *) &iov, 2, &amt);
+    rv = apr_file_writev_full(dobj->hdrs.tempfd, (const struct iovec *) &iov,
+                              2, &amt);
     if (rv != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00726)
                 "could not write info to header file %s",
                 dobj->hdrs.tempfile);
         apr_file_close(dobj->hdrs.tempfd);
         apr_pool_destroy(dobj->hdrs.pool);
