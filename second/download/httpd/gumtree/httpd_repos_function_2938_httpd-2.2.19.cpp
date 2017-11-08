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
        if (TXN_IGNORE_ERRORS(sql->trans)) {
            PGresult *res = PQexec(sql->conn, "SAVEPOINT APR_DBD_TXN_SP");
            if (res) {
                int ret = PQresultStatus(res);
                PQclear(res);
                if (!dbd_pgsql_is_success(ret)) {
                    sql->trans->errnum = ret;
                    return PGRES_FATAL_ERROR;
                }
            } else {
                return sql->trans->errnum = PGRES_FATAL_ERROR;
            }
        }
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
            if (TXN_IGNORE_ERRORS(sql->trans)) {
                PGresult *res = PQexec(sql->conn,
                                       "ROLLBACK TO SAVEPOINT APR_DBD_TXN_SP");
                if (res) {
                    int ret = PQresultStatus(res);
                    PQclear(res);
                    if (!dbd_pgsql_is_success(ret)) {
                        sql->trans->errnum = ret;
                        return PGRES_FATAL_ERROR;
                    }
                } else {
                    return sql->trans->errnum = PGRES_FATAL_ERROR;
                }
            } else if (TXN_NOTICE_ERRORS(sql->trans)){
                sql->trans->errnum = ret;
            }
            return ret;
        } else {
            if (TXN_IGNORE_ERRORS(sql->trans)) {
                PGresult *res = PQexec(sql->conn,
                                       "RELEASE SAVEPOINT APR_DBD_TXN_SP");
                if (res) {
                    int ret = PQresultStatus(res);
                    PQclear(res);
                    if (!dbd_pgsql_is_success(ret)) {
                        sql->trans->errnum = ret;
                        return PGRES_FATAL_ERROR;
                    }
                } else {
                    return sql->trans->errnum = PGRES_FATAL_ERROR;
                }
            }
        }
        if (!*results) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->res = res;
        (*results)->ntuples = PQntuples(res);
        (*results)->sz = PQnfields(res);
        (*results)->random = seek;
        (*results)->pool = pool;
        apr_pool_cleanup_register(pool, res, clear_result,
                                  apr_pool_cleanup_null);
    }
    else {
        if (TXN_IGNORE_ERRORS(sql->trans)) {
            PGresult *res = PQexec(sql->conn, "SAVEPOINT APR_DBD_TXN_SP");
            if (res) {
                int ret = PQresultStatus(res);
                PQclear(res);
                if (!dbd_pgsql_is_success(ret)) {
                    sql->trans->errnum = ret;
                    return PGRES_FATAL_ERROR;
                }
            } else {
                return sql->trans->errnum = PGRES_FATAL_ERROR;
            }
        }
        if (PQsendQuery(sql->conn, query) == 0) {
            if (TXN_IGNORE_ERRORS(sql->trans)) {
                PGresult *res = PQexec(sql->conn,
                                       "ROLLBACK TO SAVEPOINT APR_DBD_TXN_SP");
                if (res) {
                    int ret = PQresultStatus(res);
                    PQclear(res);
                    if (!dbd_pgsql_is_success(ret)) {
                        sql->trans->errnum = ret;
                        return PGRES_FATAL_ERROR;
                    }
                } else {
                    return sql->trans->errnum = PGRES_FATAL_ERROR;
                }
            } else if (TXN_NOTICE_ERRORS(sql->trans)){
                sql->trans->errnum = 1;
            }
            return 1;
        } else {
            if (TXN_IGNORE_ERRORS(sql->trans)) {
                PGresult *res = PQexec(sql->conn,
                                       "RELEASE SAVEPOINT APR_DBD_TXN_SP");
                if (res) {
                    int ret = PQresultStatus(res);
                    PQclear(res);
                    if (!dbd_pgsql_is_success(ret)) {
                        sql->trans->errnum = ret;
                        return PGRES_FATAL_ERROR;
                    }
                } else {
                    return sql->trans->errnum = PGRES_FATAL_ERROR;
                }
            }
        }
        if (*results == NULL) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->random = seek;
        (*results)->handle = sql->conn;
        (*results)->pool = pool;
    }
    return 0;
}