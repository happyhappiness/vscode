        else
            ldc->reason = "ldap_simple_bind() to check user credentials "
                          "timed out";
        ldap_msgfree(res);
        uldap_connection_unbind(ldc);
        failures++;
        goto start_over;
    }

    /* failure? if so - return */
    if (result != LDAP_SUCCESS) {
        ldc->reason = "ldap_simple_bind() to check user credentials failed";
