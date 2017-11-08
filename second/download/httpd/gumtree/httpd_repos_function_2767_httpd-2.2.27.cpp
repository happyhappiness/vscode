static int dbd_freetds_pselect(apr_pool_t *pool, apr_dbd_t *sql,
                               apr_dbd_results_t **results,
                               apr_dbd_prepared_t *statement,
                               int seek, const char **values)
{
    const char *query = dbd_statement(pool, statement,
                                      statement->nargs, values);
    return dbd_freetds_select(pool, sql, results, query, seek);
}