static int dbd_mysql_pbselect(apr_pool_t *pool, apr_dbd_t *sql,
                              apr_dbd_results_t **res,
                              apr_dbd_prepared_t *statement, int random,
                              const void **args)
{
    int ret;
    MYSQL_BIND *bind;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    bind = apr_palloc(pool, statement->nargs * sizeof(MYSQL_BIND));

    dbd_mysql_bbind(pool, statement, args, bind);

    ret = dbd_mysql_pselect_internal(pool, sql,  res, statement, random, bind);

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}