static int dbd_oracle_select(apr_pool_t *pool, apr_dbd_t *sql,
                             apr_dbd_results_t **results,
                             const char *query, int seek)
{
    int ret = 0;
    apr_dbd_prepared_t *statement = NULL;

    ret = dbd_oracle_prepare(pool, sql, query, NULL, 0, 0, NULL, &statement);
    if (ret != 0) {
        return ret;
    }

    ret = dbd_oracle_pselect(pool, sql, results, statement, seek, NULL);
    if (ret != 0) {
        return ret;
    }

    return ret;
}