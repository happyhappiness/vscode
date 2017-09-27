     char dates[APR_RFC822_DATE_LEN];
     int status;
     apr_pool_t *address_pool;
 
     /* is this for us? */
     if (proxyhost) {
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
-                     "proxy: FTP: declining URL %s - proxyhost %s specified:", url, proxyhost);
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
+                      "declining URL %s - proxyhost %s specified:", url,
+                      proxyhost);
         return DECLINED;        /* proxy connections are via HTTP */
     }
     if (strncasecmp(url, "ftp:", 4)) {
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
-                     "proxy: FTP: declining URL %s - not ftp:", url);
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
+                      "declining URL %s - not ftp:", url);
         return DECLINED;        /* only interested in FTP */
     }
-    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
-                 "proxy: FTP: serving URL %s", url);
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "serving URL %s", url);
 
 
     /*
      * I: Who Do I Connect To? -----------------------
      *
      * Break up the URL to determine the host to connect to
