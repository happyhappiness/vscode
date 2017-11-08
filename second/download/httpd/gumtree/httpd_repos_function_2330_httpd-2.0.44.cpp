static void vt_sdbm_freedatum(apr_dbm_t *dbm, apr_datum_t data)
{
    APR_DBM_FREEDPTR(data.dptr);
}