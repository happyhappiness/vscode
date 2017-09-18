        }
    }

    if (SSL_X509_getCN(ptemp, cert, &cn)) {
        int fnm_flags = FNM_PERIOD|FNM_CASE_BLIND;

        if (apr_is_fnmatch(cn) &&
            (apr_fnmatch(cn, s->server_hostname,
                         fnm_flags) == FNM_NOMATCH))
        {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate wildcard CommonName (CN) `%s' "
                         "does NOT match server name!?",
