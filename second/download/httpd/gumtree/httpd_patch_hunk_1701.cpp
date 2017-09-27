     if (rv != APR_SUCCESS) {
         mkdir_structure(conf, dobj->hdrsfile, r->pool);
     }
 
     rv = safe_file_rename(conf, dobj->tempfile, dobj->hdrsfile, r->pool);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                      "disk_cache: rename tempfile to hdrsfile failed: %s -> %s",
                      dobj->tempfile, dobj->hdrsfile);
+        apr_file_remove(dobj->tempfile, r->pool);
         return rv;
     }
 
     dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
