static int dbd_pgsql_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    PGresult *res;
    int ret;
    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    if (TXN_IGNORE_ERRORS(sql->trans)) {
        PGresult *res = PQexec(sql->conn, "SAVEPOINT APR_DBD_TXN_SP");
        if (res) {
            ret = PQresultStatus(res);
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
            /* ugh, making 0 return-success doesn't fit */
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
                ret = PQresultStatus(res);
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
                ret = PQresultStatus(res);
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