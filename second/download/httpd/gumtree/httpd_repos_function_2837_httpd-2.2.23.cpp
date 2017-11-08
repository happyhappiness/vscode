static int odbc_pvbselect(apr_pool_t *pool, apr_dbd_t *handle,
                          apr_dbd_results_t **res,
                          apr_dbd_prepared_t *statement,
                          int random, va_list args)
{
    const char **values;
    int i;

    values = apr_palloc(pool, sizeof(*values) * statement->nvals);
    for (i = 0; i < statement->nvals; i++)
        values[i] = va_arg(args, const char *);
    return odbc_pbselect(pool, handle, res, statement, random, (const void **)values);
}