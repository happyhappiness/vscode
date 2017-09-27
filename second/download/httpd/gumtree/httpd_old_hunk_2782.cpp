
    /* getting a subtype */
    while (apr_isspace(*cp)) {
        cp++;
    }
    if (!*cp) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "Cannot get media subtype.");
        return (NULL);
    }
    ctp->subtype = cp;
    do {
        cp++;
