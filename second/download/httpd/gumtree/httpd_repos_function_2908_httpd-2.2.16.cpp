static int dbd_sqlite_query(apr_dbd_t * sql, int *nrows, const char *query)
{
    char **result;
    int ret;
    int tuples = 0;
    int fields = 0;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    FREE_ERROR_MSG(sql);

    ret =
        sqlite_get_table(sql->conn, query, &result, &tuples, &fields,
                         &sql->errmsg);
    if (ret == SQLITE_OK) {
        *nrows = sqlite_changes(sql->conn);

        if (tuples > 0)
            free(result);

        ret = 0;
    }

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }

    return ret;
}