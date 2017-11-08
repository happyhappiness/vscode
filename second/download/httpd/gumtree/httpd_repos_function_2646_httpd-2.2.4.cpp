static int dbd_pgsql_pquery(apr_pool_t *pool, apr_dbd_t *sql,
                            int *nrows, apr_dbd_prepared_t *statement,
                            int nargs, const char **values)
{
    int ret;
    PGresult *res;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    if (statement->prepared) {
        res = PQexecPrepared(sql->conn, statement->name, nargs, values, 0, 0,
                             0);
    }
    else {
        res = PQexecParams(sql->conn, statement->name, nargs, 0, values, 0, 0,
                           0);
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

    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}