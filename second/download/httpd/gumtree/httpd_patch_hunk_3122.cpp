      * initialize the mutex handling
      */
     if (!ssl_mutex_init(base_server, p)) {
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 #ifdef HAVE_OCSP_STAPLING
-    if (!ssl_stapling_mutex_init(base_server, p)) {
-        return HTTP_INTERNAL_SERVER_ERROR;
-    }
-
     ssl_stapling_ex_init();
 #endif
 
     /*
      * initialize session caching
      */
     ssl_scache_init(base_server, p);
 
     /*
      *  initialize servers
      */
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, base_server,
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, base_server, APLOGNO(01887)
                  "Init: Initializing (virtual) servers for SSL");
 
     for (s = base_server; s; s = s->next) {
         sc = mySrvConfig(s);
         /*
          * Either now skip this server when SSL is disabled for
