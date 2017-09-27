     urllen = strlen(url);
     if (urllen > MAX_URL_LENGTH) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "cache: URL exceeds length threshold: %s", url);
         return DECLINED;
     }
-    /* DECLINE urls ending in / */
+    /* DECLINE urls ending in / ??? EGP: why? */
     if (url[urllen-1] == '/') {
         return DECLINED;
     }
 
     /* make space for the per request config */
     cache = (cache_request_rec *) ap_get_module_config(r->request_config, 
