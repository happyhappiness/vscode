         else {
             ldc->reason = result->reason;
         }
         return(result->rc);
     }
 
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "LDC %pp init", ldc);
+
     if (ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
         /* Now that we have an ldap struct, add it to the referral list for rebinds. */
         rc = apr_ldap_rebind_add(ldc->rebind_pool, ldc->ldap, ldc->binddn, ldc->bindpw);
         if (rc != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server, APLOGNO(01277)
                     "LDAP: Unable to add rebind cross reference entry. Out of memory?");
