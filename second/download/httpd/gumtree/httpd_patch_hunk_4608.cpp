 
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01076)
                   "url: %s proxyname: %s proxyport: %d",
                   url, proxyname, proxyport);
 
-    if (strncasecmp(url, "fcgi:", 5) != 0) {
+    if (ap_cstr_casecmpn(url, "fcgi:", 5) != 0) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01077) "declining URL %s", url);
         return DECLINED;
     }
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01078) "serving URL %s", url);
 
