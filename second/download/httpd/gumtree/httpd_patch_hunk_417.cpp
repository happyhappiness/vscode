         return ap_pass_brigade(f->next, bb);
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                  "cache: running CACHE_OUT filter");
 
-    /* cache_read_entity_headers() was called in cache_select_url() */
-    cache_read_entity_body(cache->handle, r->pool, bb);
+    /* recall_body() was called in cache_select_url() */
+    cache->provider->recall_body(cache->handle, r->pool, bb);
 
     /* This filter is done once it has served up its content */
     ap_remove_output_filter(f);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                  "cache: serving %s", r->uri);
