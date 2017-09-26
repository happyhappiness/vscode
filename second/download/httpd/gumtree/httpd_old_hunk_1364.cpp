    p = db ? db->pool : p;

    /* There might not be a <db> if we had problems creating it. */
    if (db == NULL) {
        errcode = 1;
        errstr = "Could not open property database.";
    }
    else {
        (void) apr_dbm_geterror(db->file, &errcode, errbuf, sizeof(errbuf));
        errstr = apr_pstrdup(p, errbuf);
    }

