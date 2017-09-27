             else {
                 compare_nodep->lastcompare = curtime;
                 compare_nodep->result = result;
             }
             LDAP_CACHE_UNLOCK();
         }
+
         if (LDAP_COMPARE_TRUE == result) {
             ldc->reason = "Comparison true (adding to cache)";
-            return LDAP_COMPARE_TRUE;
         }
         else if (LDAP_COMPARE_FALSE == result) {
             ldc->reason = "Comparison false (adding to cache)";
-            return LDAP_COMPARE_FALSE;
         }
-        else {
+        else if (LDAP_NO_SUCH_ATTRIBUTE == result) {
             ldc->reason = "Comparison no such attribute (adding to cache)";
-            return LDAP_NO_SUCH_ATTRIBUTE;
+        }
+        else {
+            ldc->reason = apr_psprintf(r->pool, 
+                                       "Comparison undefined: (%d): %s (adding to cache)", 
+                                        result, ldap_err2string(result));
         }
     }
+
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, 
+                  "ldap_compare_s(%pp, %s, %s, %s) = %s", 
+                  ldc->ldap, dn, attrib, value, ldap_err2string(result));
     return result;
 }
 
 
 static util_compare_subgroup_t* uldap_get_subgroups(request_rec *r,
                                                     util_ldap_connection_t *ldc,
