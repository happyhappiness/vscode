         default: {
             /* oo-er! an error */
             return rv;
         }
         }
     }
+
+    /* if Cache-Control: only-if-cached, and not cached, return 504 */
+    if (cache->control_in.only_if_cached) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00696)
+                "cache: 'only-if-cached' requested and no cached entity, "
+                "returning 504 Gateway Timeout for: %s", r->uri);
+        return HTTP_GATEWAY_TIME_OUT;
+    }
+
     return DECLINED;
 }
 
 apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
-                                        char**key)
+        const char **key)
 {
     cache_server_conf *conf;
-    cache_request_rec *cache;
     char *port_str, *hn, *lcs;
     const char *hostname, *scheme;
     int i;
     char *path, *querystring;
 
-    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
-                                                       &cache_module);
-    if (!cache) {
-        /* This should never happen */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                     "cache: No cache request information available for key"
-                     " generation");
-        *key = "";
-        return APR_EGENERAL;
-    }
-    if (cache->key) {
+    if (*key) {
         /*
          * We have been here before during the processing of this request.
-         * So return the key we already have.
          */
-        *key = apr_pstrdup(p, cache->key);
         return APR_SUCCESS;
     }
 
     /*
      * Get the module configuration. We need this for the CacheIgnoreQueryString
      * option below.
