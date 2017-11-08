static int dbd_mysql_pvbselect(apr_pool_t *pool, apr_dbd_t *sql,
                               apr_dbd_results_t **res,
                               apr_dbd_prepared_t *statement, int random,
                               va_list args)
{
    const void **values;
    int i;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    values = apr_palloc(pool, sizeof(*values) * statement->nvals);

    for (i = 0; i < statement->nvals; i++) {
        values[i] = va_arg(args, const void*);
    }

    return dbd_mysql_pbselect(pool, sql, res, statement, random, values);
}