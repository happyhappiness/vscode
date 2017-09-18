    /* rfc1035 says DNS names must consist of "[-a-zA-Z0-9]" and '.' */
    for (i = 0; apr_isalnum(addr[i]) || addr[i] == '-' || addr[i] == '.'; ++i)
        continue;

#if 0
    if (addr[i] == ':') {
    ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     "@@@@ handle optional port in proxy_is_domainname()");
	/* @@@@ handle optional port */
    }
#endif

    if (addr[i] != '\0')
