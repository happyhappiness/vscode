static int dbd_sqlite3_pquery(apr_pool_t *pool, apr_dbd_t *sql,
                              int *nrows, apr_dbd_prepared_t *statement,
                              int nargs, const char **values)
{
    sqlite3_stmt *stmt = statement->stmt;
    int ret = -1, retry_count = 0, i;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

#if APR_HAS_THREADS
    apr_thread_mutex_lock(sql->mutex);
#endif

    ret = sqlite3_reset(stmt);
    if (ret == SQLITE_OK) {
        for (i=0; i < nargs; i++) {
            sqlite3_bind_text(stmt, i + 1, values[i], strlen(values[i]),
                              SQLITE_STATIC);
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

        sqlite3_reset(stmt);
    }

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