static int dbd_freetds_pbselect(apr_pool_t *pool, apr_dbd_t *sql,
                                apr_dbd_results_t **results,
                                apr_dbd_prepared_t *statement,
                                int seek, const void **values)
{
    return DBD_NOTIMPL;
}