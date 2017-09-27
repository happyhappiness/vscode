    }

    /* getting parameters */
    cp++; /* skip the ';' */
    cp = zap_sp(cp);
    if (cp == NULL || *cp == '\0') {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "Cannot get media parameter.");
        return (NULL);
    }
    mp = cp;
    attribute = NULL;
    value = NULL;
