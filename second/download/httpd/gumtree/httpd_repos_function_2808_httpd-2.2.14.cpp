static int dbd_sqlite3_query_internal(apr_dbd_t *sql, sqlite3_stmt *stmt,
                                      int *nrows)
{
    int ret = -1, retry_count = 0;

    while(retry_count++ <= MAX_RETRY_COUNT) {
        ret = sqlite3_step(stmt);
        if (ret != SQLITE_BUSY)
            break;

        apr_dbd_mutex_unlock();
        apr_sleep(MAX_RETRY_SLEEP);
        apr_dbd_mutex_lock();
    }

    *nrows = sqlite3_changes(sql->conn);

    if (dbd_sqlite3_is_success(ret)) {
        ret = 0;
    }
    return ret;
}