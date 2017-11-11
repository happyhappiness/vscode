static int dbd_sqlite3_pbselect(apr_pool_t * pool, apr_dbd_t * sql,
                                apr_dbd_results_t ** results,
                                apr_dbd_prepared_t * statement,
                                int seek, const void **values)
{
    sqlite3_stmt *stmt = statement->stmt;
    int ret;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    apr_dbd_mutex_lock();

    ret = sqlite3_reset(stmt);
    if (ret == SQLITE_OK) {
        dbd_sqlite3_bbind(statement, values);

        ret = dbd_sqlite3_select_internal(pool, sql, results, stmt, seek);

        sqlite3_reset(stmt);
    }

    apr_dbd_mutex_unlock();

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}