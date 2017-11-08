static int dbd_mysql_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                             const char *query, const char *label,
                             int nargs, int nvals, apr_dbd_type_e *types,
                             apr_dbd_prepared_t **statement)
{
    /* Translate from apr_dbd to native query format */
    int ret;

    if (!*statement) {
        *statement = apr_palloc(pool, sizeof(apr_dbd_prepared_t));
    }
    (*statement)->stmt = mysql_stmt_init(sql->conn);

    if ((*statement)->stmt) {
        apr_pool_cleanup_register(pool, (*statement)->stmt,
                                  stmt_close, apr_pool_cleanup_null);
        ret = mysql_stmt_prepare((*statement)->stmt, query, strlen(query));

        if (ret != 0) {
            ret = mysql_stmt_errno((*statement)->stmt);
        }

        (*statement)->nargs = nargs;
        (*statement)->nvals = nvals;
        (*statement)->types = types;

        return ret;
    }

    return CR_OUT_OF_MEMORY;
}