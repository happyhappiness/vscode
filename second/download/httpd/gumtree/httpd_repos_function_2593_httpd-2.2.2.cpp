static int dbd_sqlite3_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int ret = -1, length = 0;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    length = strlen(query);
    apr_thread_mutex_lock(sql->mutex);

    do {
        ret = sqlite3_prepare(sql->conn, query, length, &stmt, &tail);
        if (ret != SQLITE_OK) {
            sqlite3_finalize(stmt);
            break;
        }
        ret = sqlite3_step(stmt);
        *nrows = sqlite3_changes(sql->conn);
        sqlite3_finalize(stmt);
        length -= (tail - query);
        query = tail;
    } while (length > 0);

    if (dbd_sqlite3_is_success(ret)) {
        ret =  0;
    }
    apr_thread_mutex_unlock(sql->mutex);
    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}