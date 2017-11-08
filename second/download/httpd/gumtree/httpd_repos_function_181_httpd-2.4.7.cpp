static dav_error * dav_generic_dbm_new_error(apr_dbm_t *db, apr_pool_t *p,
                                             apr_status_t status)
{
    int errcode;
    const char *errstr;
    dav_error *err;
    char errbuf[200];

    if (status == APR_SUCCESS) {
        return NULL;
    }

    /* There might not be a <db> if we had problems creating it. */
    if (db == NULL) {
        errcode = 1;
        errstr = "Could not open property database.";
    }
    else {
        (void) apr_dbm_geterror(db, &errcode, errbuf, sizeof(errbuf));
        errstr = apr_pstrdup(p, errbuf);
    }

    err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, errcode, status, errstr);
    return err;
}