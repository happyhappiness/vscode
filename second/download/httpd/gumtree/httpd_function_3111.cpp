static dav_error * dav_fs_dbm_error(dav_db *db, apr_pool_t *p,
                                    apr_status_t status)
{
    int errcode;
    const char *errstr;
    dav_error *err;
    char errbuf[200];

    if (status == APR_SUCCESS)
        return NULL;

    p = db ? db->pool : p;

    /* There might not be a <db> if we had problems creating it. */
    if (db == NULL) {
        errcode = 1;
        errstr = "Could not open property database.";
        if (APR_STATUS_IS_EDSOOPEN(status))
            ap_log_error(APLOG_MARK, APLOG_CRIT, status, ap_server_conf, APLOGNO(00576)
            "The DBM driver could not be loaded");
    }
    else {
        (void) apr_dbm_geterror(db->file, &errcode, errbuf, sizeof(errbuf));
        errstr = apr_pstrdup(p, errbuf);
    }

    err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, errcode, status, errstr);
    return err;
}