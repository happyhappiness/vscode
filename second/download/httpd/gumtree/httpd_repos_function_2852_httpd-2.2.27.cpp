static int dbd_sqlite3_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int ret = -1, length = 0;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    length = strlen(query);
    apr_dbd_mutex_lock();

    do {
        ret = sqlite3_prepare(sql->conn, query, length, &stmt, &tail);
        if (ret != SQLITE_OK) {
            sqlite3_finalize(stmt);
            break;
        }

        ret = dbd_sqlite3_query_internal(sql, stmt, nrows);

        sqlite3_finalize(stmt);
        length -= (tail - query);
        query = tail;
    } while (length > 0);

    apr_dbd_mutex_unlock();

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}