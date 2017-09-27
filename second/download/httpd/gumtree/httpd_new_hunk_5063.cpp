        else
            ldc->reason = "ldap_simple_bind() to check user credentials "
                          "timed out";
        ldap_msgfree(res);
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }

    /* failure? if so - return */
    if (result != LDAP_SUCCESS) {
        ldc->reason = "ldap_simple_bind() to check user credentials failed";
