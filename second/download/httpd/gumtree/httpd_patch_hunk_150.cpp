                                       "authorisation successful (attribute %s) [%s][%s]",
                                       getpid(), ent[i].name, ldc->reason, ldap_err2string(result));
                         return OK;
                     }
                     default: {
                         ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
-                                      "[%d] auth_ldap authorise: require group: "
+                                      "[%d] auth_ldap authorise: require group \"%s\": "
                                       "authorisation failed [%s][%s]",
-                                      getpid(), ldc->reason, ldap_err2string(result));
+                                      getpid(), t, ldc->reason, ldap_err2string(result));
                     }
                 }
             }
         }
     }
 
