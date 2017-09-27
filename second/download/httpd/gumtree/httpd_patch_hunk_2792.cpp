      * XXX: ldap_result() with a timeout.
      */
     if (st->opTimeout) {
         rc = apr_ldap_set_option(r->pool, ldc->ldap, LDAP_OPT_TIMEOUT,
                                  st->opTimeout, &(result));
         if (APR_SUCCESS != rc) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(01283)
                              "LDAP: Could not set LDAP_OPT_TIMEOUT");
         }
     }
 #endif
 
     return(rc);
 }
 
+static int uldap_ld_errno(util_ldap_connection_t *ldc)
+{
+    int ldaprc;
+#ifdef LDAP_OPT_ERROR_NUMBER
+    if (LDAP_SUCCESS == ldap_get_option(ldc->ldap, LDAP_OPT_ERROR_NUMBER, &ldaprc)) return ldaprc;
+#endif
+#ifdef LDAP_OPT_RESULT_CODE
+    if (LDAP_SUCCESS == ldap_get_option(ldc->ldap, LDAP_OPT_RESULT_CODE, &ldaprc)) return ldaprc;
+#endif
+    return LDAP_OTHER;
+}
+
 /*
  * Replacement function for ldap_simple_bind_s() with a timeout.
- * To do this in a portable way, we have to use ldap_simple_bind() and 
+ * To do this in a portable way, we have to use ldap_simple_bind() and
  * ldap_result().
  *
  * Returns LDAP_SUCCESS on success; and an error code on failure
  */
 static int uldap_simple_bind(util_ldap_connection_t *ldc, char *binddn,
                              char* bindpw, struct timeval *timeout)
 {
     LDAPMessage *result;
     int rc;
     int msgid = ldap_simple_bind(ldc->ldap, binddn, bindpw);
     if (msgid == -1) {
         ldc->reason = "LDAP: ldap_simple_bind() failed";
-        /* -1 is LDAP_SERVER_DOWN in openldap, use something else */
-        return LDAP_OTHER;
+        return uldap_ld_errno(ldc);
     }
     rc = ldap_result(ldc->ldap, msgid, 0, timeout, &result);
     if (rc == -1) {
         ldc->reason = "LDAP: ldap_simple_bind() result retrieval failed";
         /* -1 is LDAP_SERVER_DOWN in openldap, use something else */
-        rc = LDAP_OTHER;
+        return uldap_ld_errno(ldc);
     }
     else if (rc == 0) {
         ldc->reason = "LDAP: ldap_simple_bind() timed out";
         rc = LDAP_TIMEOUT;
     } else if (ldap_parse_result(ldc->ldap, result, &rc, NULL, NULL, NULL,
                                  NULL, 1) == -1) {
         ldc->reason = "LDAP: ldap_simple_bind() parse result failed";
+        return uldap_ld_errno(ldc);
     }
     return rc;
 }
 
 /*
  * Connect to the LDAP server and binds. Does not connect if already
