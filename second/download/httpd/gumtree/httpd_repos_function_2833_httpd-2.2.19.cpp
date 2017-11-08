static int dbd_sqlite3_select(apr_pool_t *pool, apr_dbd_t *sql,
                              apr_dbd_results_t **results, const char *query,
                              int seek)
{
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int ret;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    apr_dbd_mutex_lock();

    ret = sqlite3_prepare(sql->conn, query, strlen(query), &stmt, &tail);
    if (dbd_sqlite3_is_success(ret)) {
        ret = dbd_sqlite3_select_internal(pool, sql, results, stmt, seek);
    }
    sqlite3_finalize(stmt);

    apr_dbd_mutex_unlock();

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}