        /* connect failed */
        return res;
    }

    /* try to do the search */
    result = ldap_search_ext_s(ldc->ldap, (char *)dn, LDAP_SCOPE_BASE,
                               NULL, subgroupAttrs, 0,
                               NULL, NULL, NULL, APR_LDAP_SIZELIMIT, &sga_res);
    if (AP_LDAP_IS_SERVER_DOWN(result)) {
        ldc->reason = "ldap_search_ext_s() for subgroups failed with server"
                      " down";
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }
    if (result == LDAP_TIMEOUT && failures == 0) {
        /*
         * we are reusing a connection that doesn't seem to be active anymore
         * (firewall state drop?), let's try a new connection.
         */
        ldc->reason = "ldap_search_ext_s() for subgroups failed with timeout";
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }

    /* if there is an error (including LDAP_NO_SUCH_OBJECT) return now */
    if (result != LDAP_SUCCESS) {
        ldc->reason = "ldap_search_ext_s() for subgroups failed";
