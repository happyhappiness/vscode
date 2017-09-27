 
     if (!found) {
         New = apr_array_push(conf->dirconn);
         New->name = apr_pstrdup(parms->pool, arg);
         New->hostaddr = NULL;
 
-	if (ap_proxy_is_ipaddr(New, parms->pool)) {
+    if (ap_proxy_is_ipaddr(New, parms->pool)) {
 #if DEBUGGING
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                         "Parsed addr %s", inet_ntoa(New->addr));
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                         "Parsed mask %s", inet_ntoa(New->mask));
+        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                     "Parsed addr %s", inet_ntoa(New->addr));
+        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                     "Parsed mask %s", inet_ntoa(New->mask));
 #endif
-	}
-	else if (ap_proxy_is_domainname(New, parms->pool)) {
-            ap_str_tolower(New->name);
+    }
+    else if (ap_proxy_is_domainname(New, parms->pool)) {
+        ap_str_tolower(New->name);
 #if DEBUGGING
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                         "Parsed domain %s", New->name);
+        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                     "Parsed domain %s", New->name);
 #endif
         }
         else if (ap_proxy_is_hostname(New, parms->pool)) {
             ap_str_tolower(New->name);
 #if DEBUGGING
             ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
