static void vt_gdbm_close(apr_dbm_t *dbm)
{
    APR_DBM_CLOSE(dbm->file);
}