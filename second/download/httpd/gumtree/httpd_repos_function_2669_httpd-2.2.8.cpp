static int dbd_pgsql_select(apr_pool_t *pool, apr_dbd_t *sql,
                            apr_dbd_results_t **results,
                            const char *query, int seek)
{
    PGresult *res;
    int ret;
    if ( sql->trans && sql->trans->errnum ) {
        return sql->trans->errnum;
    }
    if (seek) { /* synchronous query */
        res = PQexec(sql->conn, query);
        if (res) {
            ret = PQresultStatus(res);
            if (dbd_pgsql_is_success(ret)) {
                ret = 0;
            } else {
                PQclear(res);
            }
        } else {
            ret = PGRES_FATAL_ERROR;
        }
        if (ret != 0) {
            if (sql->trans) {
                sql->trans->errnum = ret;
            }
            return ret;
        }
        if (!*results) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->res = res;
        (*results)->ntuples = PQntuples(res);
        (*results)->sz = PQnfields(res);
        (*results)->random = seek;
        apr_pool_cleanup_register(pool, res, clear_result,
                                  apr_pool_cleanup_null);
    }
    else {
        if (PQsendQuery(sql->conn, query) == 0) {
            if (sql->trans) {
                sql->trans->errnum = 1;
            }
            return 1;
        }
        if (*results == NULL) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->random = seek;
        (*results)->handle = sql->conn;
    }
    return 0;
}