static int dbd_freetds_pvquery(apr_pool_t *pool, apr_dbd_t *sql, int *nrows,
                               apr_dbd_prepared_t *statement, va_list args)
{
    const char **values;
    int i;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    values = apr_palloc(pool, sizeof(*values) * statement->nargs);

    for (i = 0; i < statement->nargs; i++) {
        values[i] = va_arg(args, const char*);
    }
    return dbd_freetds_pquery(pool, sql, nrows, statement, values);
}