static void vt_sdbm_close(apr_dbm_t *dbm)
{
    APR_DBM_CLOSE(dbm->file);
}