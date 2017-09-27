    }

    /* Set the alias dereferencing option */
    ldap_option = ldc->deref;
    ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &ldap_option);

    if (ldc->ChaseReferrals != AP_LDAP_CHASEREFERRALS_SDKDEFAULT) {
        /* Set options for rebind and referrals. */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01278)
                "LDAP: Setting referrals to %s.",
                ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"));
        apr_ldap_set_option(r->pool, ldc->ldap,
                APR_LDAP_OPT_REFERRALS,
