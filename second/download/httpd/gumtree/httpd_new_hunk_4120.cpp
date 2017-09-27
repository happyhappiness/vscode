    for (i = 0; apr_isalnum(addr[i]) || addr[i] == '-' || addr[i] == '.'; ++i) {
        continue;
    }

#if 0
    if (addr[i] == ':') {
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(03234)
                     "@@@@ handle optional port in proxy_is_domainname()");
    /* @@@@ handle optional port */
    }
#endif

    if (addr[i] != '\0') {
