             sec->filter = apr_pstrdup(cmd->pool, urld->lud_filter);
         }
     }
     else {
         sec->filter = "objectclass=*";
     }
-    if (strncmp(url, "ldaps", 5) == 0) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
-		     cmd->server, "[%d] auth_ldap parse url: requesting secure LDAP", getpid());
-#ifdef APU_HAS_LDAP_STARTTLS
-        sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
-        sec->starttls = 1;
-#else
-#ifdef APU_HAS_LDAP_NETSCAPE_SSL
+
+      /* "ldaps" indicates secure ldap connections desired
+      */
+    if (strncasecmp(url, "ldaps", 5) == 0)
+    {
+        sec->secure = 1;
         sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
-        sec->netscapessl = 1;
-#else
-        return "Secure LDAP (ldaps://) not supported. Rebuild APR-Util";
-#endif
-#endif
+        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server,
+                     "LDAP: auth_ldap using SSL connections");
     }
-    else {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
-		     cmd->server, "[%d] auth_ldap parse url: not requesting secure LDAP", getpid());
-        sec->netscapessl = 0;
-        sec->starttls = 0;
+    else
+    {
+        sec->secure = 0;
         sec->port = urld->lud_port? urld->lud_port : LDAP_PORT;
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, 
+                     "LDAP: auth_ldap not using SSL connections");
     }
 
     sec->have_ldap_url = 1;
     apr_ldap_free_urldesc(urld);
     return NULL;
 }
