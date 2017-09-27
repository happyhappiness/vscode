      */
 
     /* This value comes from the client's initial request. */
     cc_req = apr_table_get(r->headers_in, "Cache-Control");
     pragma = apr_table_get(r->headers_in, "Pragma");
 
-    if (ap_cache_liststr(NULL, pragma, "no-cache", NULL)
-        || ap_cache_liststr(NULL, cc_req, "no-cache", NULL)) {
+    ap_cache_control(r, &cache->control_in, cc_req, pragma, r->headers_in);
+
+    if (cache->control_in.no_cache) {
 
         if (!conf->ignorecachecontrol) {
             /* Treat as stale, causing revalidation */
             return 0;
         }
 
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
-                     "Incoming request is asking for a uncached version of "
-                     "%s, but we know better and are ignoring it",
-                     r->unparsed_uri);
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00781)
+                "Incoming request is asking for a uncached version of "
+                "%s, but we have been configured to ignore it and "
+                "serve a cached response anyway",
+                r->unparsed_uri);
     }
 
     /* These come from the cached entity. */
-    cc_cresp = apr_table_get(h->resp_hdrs, "Cache-Control");
-    expstr = apr_table_get(h->resp_hdrs, "Expires");
-
-    if (ap_cache_liststr(NULL, cc_cresp, "no-cache", NULL)) {
+    if (h->cache_obj->info.control.no_cache
+            || h->cache_obj->info.control.no_cache_header
+            || h->cache_obj->info.control.private_header) {
         /*
-         * The cached entity contained Cache-Control: no-cache, so treat as
-         * stale causing revalidation
+         * The cached entity contained Cache-Control: no-cache, or a
+         * no-cache with a header present, or a private with a header
+         * present, so treat as stale causing revalidation.
          */
         return 0;
     }
 
     if ((agestr = apr_table_get(h->resp_hdrs, "Age"))) {
         age_c = apr_atoi64(agestr);
     }
 
     /* calculate age of object */
     age = ap_cache_current_age(info, age_c, r->request_time);
 
     /* extract s-maxage */
-    if (cc_cresp && ap_cache_liststr(r->pool, cc_cresp, "s-maxage", &val)
-        && val != NULL) {
-        smaxage = apr_atoi64(val);
-    }
-    else {
-        smaxage = -1;
-    }
+    smaxage = h->cache_obj->info.control.s_maxage_value;
 
     /* extract max-age from request */
-    if (!conf->ignorecachecontrol
-        && cc_req && ap_cache_liststr(r->pool, cc_req, "max-age", &val)
-        && val != NULL) {
-        maxage_req = apr_atoi64(val);
-    }
-    else {
-        maxage_req = -1;
+    maxage_req = -1;
+    if (!conf->ignorecachecontrol) {
+        maxage_req = cache->control_in.max_age_value;
     }
 
-    /* extract max-age from response */
-    if (cc_cresp && ap_cache_liststr(r->pool, cc_cresp, "max-age", &val)
-        && val != NULL) {
-        maxage_cresp = apr_atoi64(val);
+    /*
+     * extract max-age from response, if both s-maxage and max-age, s-maxage
+     * takes priority
+     */
+    if (smaxage != -1) {
+        maxage_cresp = smaxage;
     }
     else {
-        maxage_cresp = -1;
+        maxage_cresp = h->cache_obj->info.control.max_age_value;
     }
 
     /*
      * if both maxage request and response, the smaller one takes priority
      */
     if (maxage_req == -1) {
