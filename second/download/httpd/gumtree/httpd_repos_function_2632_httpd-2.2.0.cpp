static int dbd_pgsql_pvquery(apr_pool_t *pool, apr_dbd_t *sql,
                             int *nrows, apr_dbd_prepared_t *statement,
                             va_list args)
{
    const char *arg;
    int nargs = 0;
    const char *values[QUERY_MAX_ARGS];

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }
    while ( arg = va_arg(args, const char*), arg ) {
        if ( nargs >= QUERY_MAX_ARGS) {
            va_end(args);
            return -1;
        }
        values[nargs++] = apr_pstrdup(pool, arg);
    }
    values[nargs] = NULL;
    return dbd_pgsql_pquery(pool, sql, nrows, statement, nargs, values);
}