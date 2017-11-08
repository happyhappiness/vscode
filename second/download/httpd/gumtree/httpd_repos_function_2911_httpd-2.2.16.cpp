static int dbd_sqlite_prepare(apr_pool_t * pool, apr_dbd_t * sql,
                              const char *query, const char *label,
                              int nargs, int nvals, apr_dbd_type_e *types,
                              apr_dbd_prepared_t ** statement)
{
    return APR_ENOTIMPL;
}