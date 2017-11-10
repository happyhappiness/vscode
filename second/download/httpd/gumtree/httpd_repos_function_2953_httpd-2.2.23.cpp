static int dbd_pgsql_pquery_internal(apr_pool_t *pool, apr_dbd_t *sql,
                                     int *nrows, apr_dbd_prepared_t *statement,
                                     const char **values,
                                     const int *len, const int *fmt)
{
    int ret;
    PGresult *res;

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

    if (statement->prepared) {
        res = PQexecPrepared(sql->conn, statement->name, statement->nargs,
                             values, len, fmt, 0);
    }
    else {
        res = PQexecParams(sql->conn, statement->name, statement->nargs, 0,
                           values, len, fmt, 0);
    }
    if (res) {
        ret = PQresultStatus(res);
        if (dbd_pgsql_is_success(ret)) {
            ret = 0;
        }
        *nrows = atoi(PQcmdTuples(res));
        PQclear(res);
    }
    else {
        ret = PGRES_FATAL_ERROR;
    }

    if (ret != 0){
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
                sql->trans->errnum = ret;
                return PGRES_FATAL_ERROR;
            }
        } else if (TXN_NOTICE_ERRORS(sql->trans)){
            sql->trans->errnum = ret;
        }
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
                sql->trans->errnum = ret;
                return PGRES_FATAL_ERROR;
            }
        }
    }

    return ret;
}