static int dbd_freetds_pquery(apr_pool_t *pool, apr_dbd_t *sql,
                              int *nrows, apr_dbd_prepared_t *statement,
                              const char **values)
{
    const char *query = dbd_statement(pool, statement,
                                      statement->nargs, values);
    return dbd_freetds_query(sql, nrows, query);
}