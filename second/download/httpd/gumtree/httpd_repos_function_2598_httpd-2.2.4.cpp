static int dbd_sqlite3_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int ret = -1, length = 0;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    length = strlen(query);
#if APR_HAS_THREADS
    apr_thread_mutex_lock(sql->mutex);
#endif

    do {
        int retry_count = 0;

        ret = sqlite3_prepare(sql->conn, query, length, &stmt, &tail);
        if (ret != SQLITE_OK) {
            sqlite3_finalize(stmt);
            break;
        }

        while(retry_count++ <= MAX_RETRY_COUNT) {
            ret = sqlite3_step(stmt);
            if (ret != SQLITE_BUSY)
                break;

#if APR_HAS_THREADS
            apr_thread_mutex_unlock(sql->mutex);
#endif
            apr_sleep(MAX_RETRY_SLEEP);
#if APR_HAS_THREADS
            apr_thread_mutex_lock(sql->mutex);
#endif
        }

        *nrows = sqlite3_changes(sql->conn);
        sqlite3_finalize(stmt);
        length -= (tail - query);
        query = tail;
    } while (length > 0);

    if (dbd_sqlite3_is_success(ret)) {
        ret = 0;
    }
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(sql->mutex);
#endif
    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}