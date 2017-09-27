     /*
      * Now get the global in_addr.  Note that it is not sufficient to use one
      * of the addresses from the main_server, since those aren't as likely to
      * be unique as the physical address of the machine
      */
     if ((rv = apr_gethostname(str, sizeof(str) - 1, p)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server,
-          "mod_unique_id: unable to find hostname of the server");
+        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server, APLOGNO(01563)
+          "unable to find hostname of the server");
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     if ((rv = apr_sockaddr_info_get(&sockaddr, str, AF_INET, 0, 0, p)) == APR_SUCCESS) {
         global_in_addr = sockaddr->sa.sin.sin_addr.s_addr;
     }
     else {
-        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server,
-                    "mod_unique_id: unable to find IPv4 address of \"%s\"", str);
+        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server, APLOGNO(01564)
+                    "unable to find IPv4 address of \"%s\"", str);
 #if APR_HAVE_IPV6
         if ((rv = apr_sockaddr_info_get(&sockaddr, str, AF_INET6, 0, 0, p)) == APR_SUCCESS) {
             memcpy(&global_in_addr,
                    (char *)sockaddr->ipaddr_ptr + sockaddr->ipaddr_len - sizeof(global_in_addr),
                    sizeof(global_in_addr));
-            ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server,
-                         "mod_unique_id: using low-order bits of IPv6 address "
+            ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server, APLOGNO(01565)
+                         "using low-order bits of IPv6 address "
                          "as if they were unique");
         }
         else
 #endif
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     apr_sockaddr_ip_get(&ipaddrstr, sockaddr);
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, main_server,
-                "mod_unique_id: using ip addr %s",
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, main_server, APLOGNO(01566) "using ip addr %s",
                  ipaddrstr);
 
     /*
      * If the server is pummelled with restart requests we could possibly end
      * up in a situation where we're starting again during the same second
      * that has been used in previous identifiers.  Avoid that situation.
