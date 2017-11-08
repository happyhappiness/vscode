static int dbd_sqlite3_pvquery(apr_pool_t *pool, apr_dbd_t *sql, int *nrows,
                               apr_dbd_prepared_t *statement, va_list args)
{
    const char **values;
    int i, nargs;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    nargs = sqlite3_bind_parameter_count(statement->stmt);
    values = apr_palloc(pool, sizeof(*values) * nargs);

    for (i = 0; i < nargs; i++) {
        values[i] = apr_pstrdup(pool, va_arg(args, const char*));
    }

    return dbd_sqlite3_pquery(pool, sql, nrows, statement, nargs, values);
}