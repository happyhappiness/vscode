 
         /* don't write empty buckets to the cache */
         if (!length) {
             continue;
         }
 
-        /* Attempt to create the data file at the last possible moment, if
-         * the body is empty, we don't write a file at all, and save an inode.
-         */
-        if (!dobj->data.tempfd) {
-            apr_finfo_t finfo;
-            rv = apr_file_mktemp(&dobj->data.tempfd, dobj->data.tempfile,
-                                 APR_CREATE | APR_WRITE | APR_BINARY |
-                                 APR_BUFFERED | APR_EXCL, dobj->data.pool);
+        if (!dobj->disk_info.header_only) {
+
+            /* Attempt to create the data file at the last possible moment, if
+             * the body is empty, we don't write a file at all, and save an inode.
+             */
+            if (!dobj->data.tempfd) {
+                apr_finfo_t finfo;
+                rv = apr_file_mktemp(&dobj->data.tempfd, dobj->data.tempfile,
+                        APR_CREATE | APR_WRITE | APR_BINARY | APR_BUFFERED
+                                | APR_EXCL, dobj->data.pool);
+                if (rv != APR_SUCCESS) {
+                    apr_pool_destroy(dobj->data.pool);
+                    return rv;
+                }
+                dobj->file_size = 0;
+                rv = apr_file_info_get(&finfo, APR_FINFO_IDENT,
+                        dobj->data.tempfd);
+                if (rv != APR_SUCCESS) {
+                    apr_pool_destroy(dobj->data.pool);
+                    return rv;
+                }
+                dobj->disk_info.device = finfo.device;
+                dobj->disk_info.inode = finfo.inode;
+                dobj->disk_info.has_body = 1;
+            }
+
+            /* write to the cache, leave if we fail */
+            rv = apr_file_write_full(dobj->data.tempfd, str, length, &written);
             if (rv != APR_SUCCESS) {
+                ap_log_rerror(
+                        APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00731) "Error when writing cache file for URL %s", h->cache_obj->key);
+                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                 apr_pool_destroy(dobj->data.pool);
                 return rv;
             }
-            dobj->file_size = 0;
-            rv = apr_file_info_get(&finfo, APR_FINFO_IDENT,
-                    dobj->data.tempfd);
-            if (rv != APR_SUCCESS) {
+            dobj->file_size += written;
+            if (dobj->file_size > dconf->maxfs) {
+                ap_log_rerror(
+                        APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00732) "URL %s failed the size check "
+                        "(%" APR_OFF_T_FMT ">%" APR_OFF_T_FMT ")", h->cache_obj->key, dobj->file_size, dconf->maxfs);
+                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                 apr_pool_destroy(dobj->data.pool);
-                return rv;
+                return APR_EGENERAL;
             }
-            dobj->disk_info.device = finfo.device;
-            dobj->disk_info.inode = finfo.inode;
-            dobj->disk_info.has_body = 1;
-        }
 
-        /* write to the cache, leave if we fail */
-        rv = apr_file_write_full(dobj->data.tempfd, str, length, &written);
-        if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00731)
-                    "Error when writing cache file for URL %s",
-                    h->cache_obj->key);
-            /* Remove the intermediate cache file and return non-APR_SUCCESS */
-            apr_pool_destroy(dobj->data.pool);
-            return rv;
-        }
-        dobj->file_size += written;
-        if (dobj->file_size > dconf->maxfs) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00732)
-                    "URL %s failed the size check "
-                    "(%" APR_OFF_T_FMT ">%" APR_OFF_T_FMT ")",
-                    h->cache_obj->key, dobj->file_size, dconf->maxfs);
-            /* Remove the intermediate cache file and return non-APR_SUCCESS */
-            apr_pool_destroy(dobj->data.pool);
-            return APR_EGENERAL;
         }
 
         /* have we reached the limit of how much we're prepared to write in one
          * go? If so, leave, we'll get called again. This prevents us from trying
          * to swallow too much data at once, or taking so long to write the data
          * the client times out.
