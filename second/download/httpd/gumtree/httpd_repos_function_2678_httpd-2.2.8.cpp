static int dbd_pgsql_pselect(apr_pool_t *pool, apr_dbd_t *sql,
                             apr_dbd_results_t **results,
                             apr_dbd_prepared_t *statement,
                             int seek, int nargs, const char **values)
{
    PGresult *res;
    int rv;
    int ret = 0;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    if (seek) { /* synchronous query */
        if (statement->prepared) {
            res = PQexecPrepared(sql->conn, statement->name, nargs, values, 0,
                                 0, 0);
        }
        else {
            res = PQexecParams(sql->conn, statement->name, nargs, 0, values, 0,
                               0, 0);
        }
        if (res) {
            ret = PQresultStatus(res);
            if (dbd_pgsql_is_success(ret)) {
                ret = 0;
            }
            else {
                PQclear(res);
            }
        }
        else {
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
        if (statement->prepared) {
            rv = PQsendQueryPrepared(sql->conn, statement->name, nargs, values,
                                     0, 0, 0);
        }
        else {
            rv = PQsendQueryParams(sql->conn, statement->name, nargs, 0,
                                   values, 0, 0, 0);
        }
        if (rv == 0) {
            if (sql->trans) {
                sql->trans->errnum = 1;
            }
            return 1;
        }
        if (!*results) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->random = seek;
        (*results)->handle = sql->conn;
    }

    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}