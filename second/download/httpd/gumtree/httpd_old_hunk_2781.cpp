    /* getting a type */
    cp = mp;
    while (apr_isspace(*cp)) {
        cp++;
    }
    if (!*cp) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "mod_mime: analyze_ct: cannot get media type from '%s'",
                     (const char *) mp);
        return (NULL);
    }
    ctp->type = cp;
    do {
        cp++;
    } while (*cp && (*cp != '/') && !apr_isspace(*cp) && (*cp != ';'));
    if (!*cp || (*cp == ';')) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "Cannot get media type from '%s'",
                     (const char *) mp);
        return (NULL);
    }
    while (apr_isspace(*cp)) {
        cp++;
    }
    if (*cp != '/') {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "mod_mime: analyze_ct: cannot get media type from '%s'",
                     (const char *) mp);
        return (NULL);
    }
    ctp->type_len = cp - ctp->type;

