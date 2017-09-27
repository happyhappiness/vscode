         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "disk_cache: URL %s partial content response not cached",
                      key);
         return DECLINED;
     }
 
+    /* Note, len is -1 if unknown so don't trust it too hard */
+    if (len > conf->maxfs) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "disk_cache: URL %s failed the size check "
+                     "(%" APR_OFF_T_FMT " > %" APR_OFF_T_FMT ")",
+                     key, len, conf->maxfs);
+        return DECLINED;
+    }
+    if (len >= 0 && len < conf->minfs) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "disk_cache: URL %s failed the size check "
+                     "(%" APR_OFF_T_FMT " < %" APR_OFF_T_FMT ")",
+                     key, len, conf->minfs);
+        return DECLINED;
+    }
+
     /* Allocate and initialize cache_object_t and disk_cache_object_t */
     h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(*obj));
     obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(*dobj));
 
     obj->key = apr_pstrdup(r->pool, key);
 
