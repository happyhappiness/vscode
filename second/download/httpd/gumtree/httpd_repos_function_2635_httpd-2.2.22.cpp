static apr_status_t set_error(apr_dbm_t *dbm, apr_status_t dbm_said)
{
    dbm->errcode = dbm_said;

    if (dbm_said != APR_SUCCESS) {
        dbm->errmsg = apr_psprintf(dbm->pool, "%pm", &dbm_said);
    } else {
        dbm->errmsg = NULL;
    }

    return dbm_said;
}