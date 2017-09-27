                     ldc->reason = "Comparison false (cached)";
                 }
                 else if (LDAP_NO_SUCH_ATTRIBUTE == compare_nodep->result) {
                     ldc->reason = "Comparison no such attribute (cached)";
                 }
                 else {
-                    ldc->reason = "Comparison undefined (cached)";
+                    ldc->reason = apr_psprintf(r->pool, 
+                                              "Comparison undefined: (%d): %s (adding to cache)", 
+                                              result, ldap_err2string(result));
                 }
 
                 /* record the result code to return with the reason... */
                 result = compare_nodep->result;
                 /* and unlock this read lock */
                 LDAP_CACHE_UNLOCK();
+
+                ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, 
+                              "ldap_compare_s(%pp, %s, %s, %s) = %s (cached)", 
+                              ldc->ldap, dn, attrib, value, ldap_err2string(result));
                 return result;
             }
         }
         /* unlock this read lock */
         LDAP_CACHE_UNLOCK();
     }
