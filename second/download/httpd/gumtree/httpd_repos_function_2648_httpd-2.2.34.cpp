static apr_status_t set_error(apr_dbm_t *dbm, apr_status_t dbm_said)
{
    apr_status_t rv = APR_SUCCESS;

    /* ### ignore whatever the DBM said (dbm_said); ask it explicitly */

    dbm->errmsg = NULL;
    if (dbm_error((DBM*)dbm->file)) {
        dbm->errmsg = NULL;
        rv = APR_EGENERAL;        /* ### need something better */
    }

    /* captured it. clear it now. */
    dbm_clearerr((DBM*)dbm->file);

    return rv;
}