              */
             addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
         }
 
         if (This->addr.s_addr == (addr.s_addr & This->mask.s_addr)) {
 #if DEBUGGING
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00903)
                          "1)IP-Match: %s[%s] <-> ", host, inet_ntoa(addr));
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00904)
                          "%s/", inet_ntoa(This->addr));
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00905)
                          "%s", inet_ntoa(This->mask));
 #endif
             return 1;
         }
 #if DEBUGGING
         else {
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00906)
                          "1)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(addr));
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00907)
                          "%s/", inet_ntoa(This->addr));
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00908)
                          "%s", inet_ntoa(This->mask));
         }
 #endif
     }
     else {
         struct apr_sockaddr_t *reqaddr;
 
         if (apr_sockaddr_info_get(&reqaddr, host, APR_UNSPEC, 0, 0, r->pool)
             != APR_SUCCESS) {
 #if DEBUGGING
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00909)
              "2)IP-NoMatch: hostname=%s msg=Host not found", host);
 #endif
             return 0;
         }
 
         /* Try to deal with multiple IP addr's for a host */
         /* FIXME: This needs to be able to deal with IPv6 */
         while (reqaddr) {
             ip = (struct in_addr *) reqaddr->ipaddr_ptr;
             if (This->addr.s_addr == (ip->s_addr & This->mask.s_addr)) {
 #if DEBUGGING
-                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00910)
                              "3)IP-Match: %s[%s] <-> ", host, inet_ntoa(*ip));
-                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00911)
                              "%s/", inet_ntoa(This->addr));
-                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00912)
                              "%s", inet_ntoa(This->mask));
 #endif
                 return 1;
             }
 #if DEBUGGING
             else {
-                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00913)
                              "3)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(*ip));
-                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00914)
                              "%s/", inet_ntoa(This->addr));
-                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00915)
                              "%s", inet_ntoa(This->mask));
             }
 #endif
             reqaddr = reqaddr->next;
         }
     }
