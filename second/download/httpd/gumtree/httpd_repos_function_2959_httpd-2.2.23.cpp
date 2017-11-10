static int dbd_pgsql_pvselect(apr_pool_t *pool, apr_dbd_t *sql,
                              apr_dbd_results_t **results,
                              apr_dbd_prepared_t *statement,
                              int seek, va_list args)
{
    const char **values;
    int i;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    values = apr_palloc(pool, sizeof(*values) * statement->nvals);

    for (i = 0; i < statement->nvals; i++) {
        values[i] = va_arg(args, const char*);
    }

    return dbd_pgsql_pselect(pool, sql, results, statement, seek, values);
}