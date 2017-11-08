static int odbc_pvbquery(apr_pool_t *pool, apr_dbd_t *handle, int *nrows,
                         apr_dbd_prepared_t *statement, va_list args)
{
    const char **values;
    int i;

    values = apr_palloc(pool, sizeof(*values) * statement->nvals);
    for (i = 0; i < statement->nvals; i++)
        values[i] = va_arg(args, const char *);
    return odbc_pbquery(pool, handle, nrows, statement, (const void **)values);
}