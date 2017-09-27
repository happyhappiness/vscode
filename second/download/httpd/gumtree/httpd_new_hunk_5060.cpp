                            (char *)value);
    if (AP_LDAP_IS_SERVER_DOWN(result)) {
        /* connection failed - try again */
        ldc->reason = "ldap_compare_s() failed with server down";
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
        ldc->reason = "ldap_compare_s() failed with timeout";
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }

    ldc->reason = "Comparison complete";
    if ((LDAP_COMPARE_TRUE == result) ||
        (LDAP_COMPARE_FALSE == result) ||
