ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01279)
                    "Unable to set LDAP_OPT_REFERRALS option to %s: %d.",
                    ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"),
                    result->rc);