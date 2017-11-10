static int dbd_pgsql_pbselect(apr_pool_t * pool, apr_dbd_t * sql,
                              apr_dbd_results_t ** results,
                              apr_dbd_prepared_t * statement,
                              int seek, const void **values)
{
    int *len, *fmt;
    const char **val;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    val = apr_palloc(pool, sizeof(*val) * statement->nargs);
    len = apr_pcalloc(pool, sizeof(*len) * statement->nargs);
    fmt = apr_pcalloc(pool, sizeof(*fmt) * statement->nargs);

    dbd_pgsql_bbind(pool, statement, values, val, len, fmt);

    return dbd_pgsql_pselect_internal(pool, sql, results, statement,
                                      seek, val, len, fmt);
}