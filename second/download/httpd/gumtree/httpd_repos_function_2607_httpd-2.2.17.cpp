static void vt_ndbm_close(apr_dbm_t *dbm)
{
    dbm_close(dbm->file);
}