    p = db ? db->pool : p;

    /* There might not be a <db> if we had problems creating it. */
    if (db == NULL) {
        errcode = 1;
        errstr = "Could not open property database.";
        if (APR_STATUS_IS_EDSOOPEN(status))
            ap_log_error(APLOG_MARK, APLOG_CRIT, status, NULL,
                         "The DBM driver could not be loaded");
    }
    else {
        (void) apr_dbm_geterror(db->file, &errcode, errbuf, sizeof(errbuf));
        errstr = apr_pstrdup(p, errbuf);
    }

