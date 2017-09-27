         /* This assumes that the tempfile is on the same file system
          * as the cache_root. If not, then we need a file copy/move
          * rather than a rename.
          */
         rv = apr_file_rename(dobj->tempfile, dobj->datafile, r->pool);
         if (rv != APR_SUCCESS) {
-            /* XXX log */
+            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
+                         "disk_cache: rename tempfile to datafile failed:"
+                         " %s -> %s", dobj->tempfile, dobj->datafile);
+            apr_file_remove(dobj->tempfile, r->pool);
         }
 
         dobj->tfd = NULL;
     }
 
     return APR_SUCCESS;
