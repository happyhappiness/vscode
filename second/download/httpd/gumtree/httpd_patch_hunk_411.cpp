                                       "authorisation failed [%s][%s]",
                                       getpid(), t, ldc->reason, ldap_err2string(result));
                     }
                 }
             }
         }
+        else if (strcmp(w, "ldap-attribute") == 0) {
+            while (t[0]) {
+                w = ap_getword(r->pool, &t, '=');
+                value = ap_getword_conf(r->pool, &t);
+
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
+                              "[%d] auth_ldap authorise: checking attribute"
+                              " %s has value %s", getpid(), w, value);
+                result = util_ldap_cache_compare(r, ldc, sec->url, req->dn,
+                                                 w, value);
+                switch(result) {
+                    case LDAP_COMPARE_TRUE: {
+                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 
+                                      0, r, "[%d] auth_ldap authorise: "
+                                      "require attribute: authorisation "
+                                      "successful", getpid());
+                        return OK;
+                    }
+                    default: {
+                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 
+                                      0, r, "[%d] auth_ldap authorise: "
+                                      "require attribute: authorisation "
+                                      "failed [%s][%s]", getpid(), 
+                                      ldc->reason, ldap_err2string(result));
+                    }
+                }
+            }
+        }
     }
 
     if (!method_restricted) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
                       "[%d] auth_ldap authorise: agreeing because non-restricted", 
                       getpid());
