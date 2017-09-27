         continue;
 
 #if 0
     if (addr[i] == ':') {
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                      "@@@@ handle optional port in proxy_is_domainname()");
-	/* @@@@ handle optional port */
+    /* @@@@ handle optional port */
     }
 #endif
 
     if (addr[i] != '\0')
         return 0;
 
