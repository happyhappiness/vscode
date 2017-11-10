static int dbd_freetds_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }
    *nrows = 0;
    sql->err = freetds_exec(sql->proc, query, 0, nrows);

    if (sql->err != SUCCEED) {
        if (sql->trans) {
            sql->trans->errnum = sql->err;
        }
        return 1;
    }
    return 0;
}