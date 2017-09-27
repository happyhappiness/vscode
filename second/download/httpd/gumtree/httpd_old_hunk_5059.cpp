    if (AP_LDAP_IS_SERVER_DOWN(result))
    {
        ldc->reason = "DN Comparison ldap_search_ext_s() "
                      "failed with server down";
        uldap_connection_unbind(ldc);
        failures++;
        goto start_over;
    }
    if (result == LDAP_TIMEOUT && failures == 0) {
        /*
         * we are reusing a connection that doesn't seem to be active anymore
         * (firewall state drop?), let's try a new connection.
         */
        ldc->reason = "DN Comparison ldap_search_ext_s() "
                      "failed with timeout";
        uldap_connection_unbind(ldc);
        failures++;
        goto start_over;
    }
    if (result != LDAP_SUCCESS) {
        /* search for reqdn failed - no match */
        ldc->reason = "DN Comparison ldap_search_ext_s() failed";
        return result;
