static void vt_gdbm_freedatum(apr_dbm_t *dbm, apr_datum_t data)
{
    (void) apr_pool_cleanup_run(dbm->pool, data.dptr, datum_cleanup);
}