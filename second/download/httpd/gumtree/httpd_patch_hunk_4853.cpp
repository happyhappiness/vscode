                         "could not create vary file %s",
                         dobj->vary.tempfile);
                 return rv;
             }
 
             amt = sizeof(format);
-            rv = apr_file_write(dobj->vary.tempfd, &format, &amt);
+            rv = apr_file_write_full(dobj->vary.tempfd, &format, amt, NULL);
             if (rv != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00722)
                         "could not write to vary file %s",
                         dobj->vary.tempfile);
                 apr_file_close(dobj->vary.tempfd);
                 apr_pool_destroy(dobj->vary.pool);
                 return rv;
             }
 
             amt = sizeof(h->cache_obj->info.expire);
-            rv = apr_file_write(dobj->vary.tempfd, &h->cache_obj->info.expire,
-                    &amt);
+            rv = apr_file_write_full(dobj->vary.tempfd,
+                                     &h->cache_obj->info.expire, amt, NULL);
             if (rv != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00723)
                         "could not write to vary file %s",
                         dobj->vary.tempfile);
                 apr_file_close(dobj->vary.tempfd);
                 apr_pool_destroy(dobj->vary.pool);
