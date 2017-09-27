 		      "[%d] auth_ldap authenticate: "
 		      "ap_get_basic_auth_pw() returns %d", getpid(), result);
         util_ldap_connection_close(ldc);
         return result;
     }
 
+    if (r->user == NULL) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
+		      "[%d] auth_ldap authenticate: no user specified", getpid());
+        util_ldap_connection_close(ldc);
+        return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
+    }
+
     /* build the username filter */
     mod_auth_ldap_build_filter(filtbuf, r, sec);
 
     /* do the user search */
     result = util_ldap_cache_checkuserid(r, ldc, sec->url, sec->basedn, sec->scope,
                                          sec->attributes, filtbuf, sent_pw, &dn, &vals);
     util_ldap_connection_close(ldc);
 
     /* sanity check - if server is down, retry it up to 5 times */
     if (result == LDAP_SERVER_DOWN) {
-        util_ldap_connection_destroy(ldc);
         if (failures++ <= 5) {
             goto start_over;
         }
     }
 
     /* handle bind failure */
