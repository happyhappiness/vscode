ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, r->server, APLOGNO(01278)
                "LDAP: Setting referrals to %s.",
                ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"));