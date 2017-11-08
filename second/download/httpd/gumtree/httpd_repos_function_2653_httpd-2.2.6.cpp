static int dbd_pgsql_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    PGresult *res;
    int ret;
    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
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
    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}