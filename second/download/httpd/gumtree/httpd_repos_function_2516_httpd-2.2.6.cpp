static apr_status_t set_error(apr_dbm_t *dbm, apr_status_t dbm_said)
{
    apr_status_t rv = APR_SUCCESS;

    /* ### ignore whatever the DBM said (dbm_said); ask it explicitly */

    if (dbm_said == APR_SUCCESS) {
        dbm->errcode = 0;
        dbm->errmsg = NULL;
    }
    else {
        /* ### need to fix. dberr was tossed in db2s(). */
        /* ### use db_strerror() */
        dbm->errcode = dbm_said;
#if DB_VER == 1 || DB_VER == 2
        dbm->errmsg = NULL;
#else
        dbm->errmsg = db_strerror(dbm_said - APR_OS_START_USEERR);
#endif
        rv = dbm_said;
    }

    return rv;
}