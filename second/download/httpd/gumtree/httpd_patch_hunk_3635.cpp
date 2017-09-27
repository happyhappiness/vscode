         wshared = ap_malloc(sizeof(proxy_worker_shared));  /* will be freed ap_proxy_share_worker */
     else
         wshared = apr_palloc(p, sizeof(proxy_worker_shared));
 
     memset(wshared, 0, sizeof(proxy_worker_shared));
 
+    if (uri.port && uri.port == ap_proxy_port_of_scheme(uri.scheme)) {
+        uri.port = 0;
+    }
     ptr = apr_uri_unparse(p, &uri, APR_URI_UNP_REVEALPASSWORD);
     if (PROXY_STRNCPY(wshared->name, ptr) != APR_SUCCESS) {
-        return apr_psprintf(p, "worker name (%s) too long", ptr);
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(02808)
+        "Alert! worker name (%s) too long; truncated to: %s", ptr, wshared->name);
     }
     if (PROXY_STRNCPY(wshared->scheme, uri.scheme) != APR_SUCCESS) {
         return apr_psprintf(p, "worker scheme (%s) too long", uri.scheme);
     }
     if (PROXY_STRNCPY(wshared->hostname, uri.hostname) != APR_SUCCESS) {
         return apr_psprintf(p, "worker hostname (%s) too long", uri.hostname);
