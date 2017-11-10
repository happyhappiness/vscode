static apr_dbd_t *dbd_freetds_open(apr_pool_t *pool, const char *params,
                                   const char **error)
{
    apr_dbd_t *sql;
    /* FIXME - pass error message back to the caller in case of failure */
    DBPROCESS *process = freetds_open(pool, params, error);
    if (process == NULL) {
        return NULL;
    }
    sql = apr_palloc (pool, sizeof (apr_dbd_t));
    sql->pool = pool;
    sql->proc = process;
    sql->params = params;
    return sql;
}