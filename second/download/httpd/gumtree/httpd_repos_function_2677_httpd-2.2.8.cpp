static int dbd_pgsql_pvquery(apr_pool_t *pool, apr_dbd_t *sql,
                             int *nrows, apr_dbd_prepared_t *statement,
                             va_list args)
{
    const char **values;
    int i;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    values = apr_palloc(pool, sizeof(*values) * statement->nargs);

    for (i = 0; i < statement->nargs; i++) {
        values[i] = apr_pstrdup(pool, va_arg(args, const char*));
    }

    return dbd_pgsql_pquery(pool, sql, nrows, statement,
                            statement->nargs, values);
}