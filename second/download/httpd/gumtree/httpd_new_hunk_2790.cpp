    }

    /* Set the alias dereferencing option */
    ldap_option = ldc->deref;
    ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &ldap_option);

    if (ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
        /* Set options for rebind and referrals. */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01278)
                "LDAP: Setting referrals to %s.",
                ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"));
        apr_ldap_set_option(r->pool, ldc->ldap,
                APR_LDAP_OPT_REFERRALS,
                (void *)((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ?
                    LDAP_OPT_ON : LDAP_OPT_OFF),
                &(result));
        if (result->rc != LDAP_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01279)
                    "Unable to set LDAP_OPT_REFERRALS option to %s: %d.",
                    ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"),
                    result->rc);
            result->reason = "Unable to set LDAP_OPT_REFERRALS.";
            ldc->reason = result->reason;
            uldap_connection_unbind(ldc);
            return(result->rc);
        }

        if ((ldc->ReferralHopLimit != AP_LDAP_HOPLIMIT_UNSET) && ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
            /* Referral hop limit - only if referrals are enabled and a hop limit is explicitly requested */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01280)
                    "Setting referral hop limit to %d.",
                    ldc->ReferralHopLimit);
            apr_ldap_set_option(r->pool, ldc->ldap,
                    APR_LDAP_OPT_REFHOPLIMIT,
                    (void *)&ldc->ReferralHopLimit,
                    &(result));
            if (result->rc != LDAP_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01281)
                        "Unable to set LDAP_OPT_REFHOPLIMIT option to %d: %d.",
                        ldc->ReferralHopLimit,
                        result->rc);
                result->reason = "Unable to set LDAP_OPT_REFHOPLIMIT.";
                ldc->reason = result->reason;
                uldap_connection_unbind(ldc);
                return(result->rc);
            }
        }
    }

/*XXX All of the #ifdef's need to be removed once apr-util 1.2 is released */
#ifdef APR_LDAP_OPT_VERIFY_CERT
    apr_ldap_set_option(r->pool, ldc->ldap, APR_LDAP_OPT_VERIFY_CERT,
