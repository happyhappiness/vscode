static apr_status_t set_error(apr_dbm_t *dbm, apr_status_t dbm_said)
{
    apr_status_t rv = APR_SUCCESS;

    /* ### ignore whatever the DBM said (dbm_said); ask it explicitly */

    if ((dbm->errcode = gdbm_errno) == GDBM_NO_ERROR) {
        dbm->errmsg = NULL;
    }
    else {
        dbm->errmsg = gdbm_strerror(gdbm_errno);
        rv = APR_EGENERAL;        /* ### need something better */
    }

    /* captured it. clear it now. */
    gdbm_errno = GDBM_NO_ERROR;

    return rv;
}