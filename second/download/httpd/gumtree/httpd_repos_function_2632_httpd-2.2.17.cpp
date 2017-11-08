static void vt_sdbm_close(apr_dbm_t *dbm)
{
    apr_sdbm_close(dbm->file);
}