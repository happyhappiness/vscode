                                   "require dn: authorisation successful", getpid());
                     return OK;
                 }
                 default: {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
                                   "[%d] auth_ldap authorise: "
-                                  "require dn: LDAP error [%s][%s]",
-                                  getpid(), ldc->reason, ldap_err2string(result));
+                                  "require dn \"%s\": LDAP error [%s][%s]",
+                                  getpid(), t, ldc->reason, ldap_err2string(result));
                 }
             }
         }
         else if (strcmp(w, "group") == 0) {
             struct mod_auth_ldap_groupattr_entry_t *ent = (struct mod_auth_ldap_groupattr_entry_t *) sec->groupattr->elts;
             int i;
