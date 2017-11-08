static apr_dbd_t *dbd_sqlite3_open(apr_pool_t *pool, const char *params)
{
    apr_dbd_t *sql = NULL;
    sqlite3 *conn = NULL;
    apr_status_t res;
    int sqlres;
    if (!params)
        return NULL;
    sqlres = sqlite3_open(params, &conn);
    if (sqlres != SQLITE_OK) {
        sqlite3_close(conn);
        return NULL;
    }
    /* should we register rand or power functions to the sqlite VM? */
    sql = apr_pcalloc(pool, sizeof(*sql));
    sql->conn = conn;
    sql->pool = pool;
    sql->trans = NULL;
    /* Create a mutex */
    res = apr_thread_mutex_create(&sql->mutex, APR_THREAD_MUTEX_DEFAULT,
                                  pool);
    if (res != APR_SUCCESS) {
        return NULL;
    }

    return sql;
}