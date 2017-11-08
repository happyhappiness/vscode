static int dbd_mysql_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                             const char *query, const char *label,
                             apr_dbd_prepared_t **statement)
{
    /* Translate from apr_dbd to native query format */
    char *myquery = apr_pstrdup(pool, query);
    char *p = myquery;
    const char *q;
    int ret;
    for (q = query; *q; ++q) {
        if (q[0] == '%') {
            if (isalpha(q[1])) {
                *p++ = '?';
                ++q;
            }
            else if (q[1] == '%') {
                /* reduce %% to % */
                *p++ = *q++;
            }
            else {
                *p++ = *q;
            }
        }
        else {
            *p++ = *q;
        }
    } 
    *p = 0;
    if (!*statement) {
        *statement = apr_palloc(pool, sizeof(apr_dbd_prepared_t));
    }
    (*statement)->stmt = mysql_stmt_init(sql->conn);

    if ((*statement)->stmt) {
        apr_pool_cleanup_register(pool, (*statement)->stmt,
                                  stmt_close, apr_pool_cleanup_null);
        ret = mysql_stmt_prepare((*statement)->stmt, myquery, strlen(myquery));

        if (ret != 0) {
            ret = mysql_stmt_errno((*statement)->stmt);
        }

        return ret;
    }

    return CR_OUT_OF_MEMORY;
}