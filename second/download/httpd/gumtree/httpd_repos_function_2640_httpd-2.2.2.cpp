static int dbd_pgsql_pvselect(apr_pool_t *pool, apr_dbd_t *sql,
                              apr_dbd_results_t **results,
                              apr_dbd_prepared_t *statement,
                              int seek, va_list args)
{
    const char *arg;
    int nargs = 0;
    const char *values[QUERY_MAX_ARGS];

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    while (arg = va_arg(args, const char*), arg) {
        if ( nargs >= QUERY_MAX_ARGS) {
            va_end(args);
            return -1;
        }
        values[nargs++] = apr_pstrdup(pool, arg);
    }
    return dbd_pgsql_pselect(pool, sql, results, statement,
                             seek, nargs, values) ;
}