                     result->rc);
             result->reason = "Unable to set LDAP_OPT_REFERRALS.";
             ldc->reason = result->reason;
             uldap_connection_unbind(ldc);
             return(result->rc);
         }
+    }
 
+    if (ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
         if ((ldc->ReferralHopLimit != AP_LDAP_HOPLIMIT_UNSET) && ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
             /* Referral hop limit - only if referrals are enabled and a hop limit is explicitly requested */
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01280)
                     "Setting referral hop limit to %d.",
                     ldc->ReferralHopLimit);
             apr_ldap_set_option(r->pool, ldc->ldap,
