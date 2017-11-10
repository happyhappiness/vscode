static int dbd_mysql_select(apr_pool_t *pool, apr_dbd_t *sql,
                            apr_dbd_results_t **results,
                            const char *query, int seek)
{
    int sz;
    int ret;
    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }
    ret = mysql_query(sql->conn, query);
    if (!ret) {
        if (sz = mysql_field_count(sql->conn), sz > 0) {
            if (!*results) {
                *results = apr_palloc(pool, sizeof(apr_dbd_results_t));
            }
            (*results)->random = seek;
            (*results)->statement = NULL;
            (*results)->pool = pool;
            if (seek) {
                (*results)->res = mysql_store_result(sql->conn);
            }
            else {
                (*results)->res = mysql_use_result(sql->conn);
            }
            apr_pool_cleanup_register(pool, (*results)->res,
                                      free_result,apr_pool_cleanup_null);
        }
    } else {
        ret = mysql_errno(sql->conn);
    }

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}