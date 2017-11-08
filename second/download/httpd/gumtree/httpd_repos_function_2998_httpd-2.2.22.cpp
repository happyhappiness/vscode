static int dbd_mysql_pbquery(apr_pool_t *pool, apr_dbd_t *sql,
                             int *nrows, apr_dbd_prepared_t *statement,
                             const void **values)
{
    MYSQL_BIND *bind;
    int ret;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    bind = apr_palloc(pool, statement->nargs * sizeof(MYSQL_BIND));

    dbd_mysql_bbind(pool, statement, values, bind);

    ret = dbd_mysql_pquery_internal(pool, sql, nrows, statement, bind);

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}