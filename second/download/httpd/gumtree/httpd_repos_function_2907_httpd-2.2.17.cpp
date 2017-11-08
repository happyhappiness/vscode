static int dbd_sqlite_select(apr_pool_t * pool, apr_dbd_t * sql,
                             apr_dbd_results_t ** results, const char *query,
                             int seek)
{
    char **result;
    int ret = 0;
    int tuples = 0;
    int fields = 0;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    FREE_ERROR_MSG(sql);

    ret = sqlite_get_table(sql->conn, query, &result, &tuples, &fields,
                          &sql->errmsg);

    if (ret == SQLITE_OK) {
        if (!*results) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }

        (*results)->res = result;
        (*results)->ntuples = tuples;
        (*results)->sz = fields;
        (*results)->random = seek;
        (*results)->pool = pool;

        if (tuples > 0)
            apr_pool_cleanup_register(pool, result, free_table,
                                      apr_pool_cleanup_null);

        ret = 0;
    }
    else {
        if (TXN_NOTICE_ERRORS(sql->trans)) {
            sql->trans->errnum = ret;
        }
    }

    return ret;
}