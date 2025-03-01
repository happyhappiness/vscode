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
        if (seek) {
            (*results)->ntuples = tuples;
        }
        else {
            (*results)->ntuples = -1;
        }
        (*results)->sz = fields;
        (*results)->random = seek;

        if (tuples > 0)
            apr_pool_cleanup_register(pool, result, (void *) free,
                                      apr_pool_cleanup_null);

        ret = 0;
    }
    else {
        sql->trans->errnum = ret;
    }

    return ret;
}