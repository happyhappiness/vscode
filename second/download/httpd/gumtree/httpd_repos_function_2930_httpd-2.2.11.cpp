static int dbd_mysql_pvquery(apr_pool_t *pool, apr_dbd_t *sql, int *nrows,
                             apr_dbd_prepared_t *statement, va_list args)
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

    return dbd_mysql_pquery(pool, sql, nrows, statement, values);
}