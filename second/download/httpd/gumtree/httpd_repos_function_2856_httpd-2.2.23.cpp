static int dbd_sqlite3_pbquery(apr_pool_t * pool, apr_dbd_t * sql,
                               int *nrows, apr_dbd_prepared_t * statement,
                               const void **values)
{
    sqlite3_stmt *stmt = statement->stmt;
    int ret = -1;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    apr_dbd_mutex_lock();

    ret = sqlite3_reset(stmt);
    if (ret == SQLITE_OK) {
        dbd_sqlite3_bbind(statement, values);

        ret = dbd_sqlite3_query_internal(sql, stmt, nrows);

        sqlite3_reset(stmt);
    }

    apr_dbd_mutex_unlock();

    if (TXN_NOTICE_ERRORS(sql->trans)) {
        sql->trans->errnum = ret;
    }
    return ret;
}