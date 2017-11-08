static apr_dbd_t *dbd_sqlite3_open(apr_pool_t *pool, const char *params,
                                   const char **error)
{
    apr_dbd_t *sql = NULL;
    sqlite3 *conn = NULL;
    int sqlres;
    if (!params)
        return NULL;
    sqlres = sqlite3_open(params, &conn);
    if (sqlres != SQLITE_OK) {
        if (error) {
            *error = apr_pstrdup(pool, sqlite3_errmsg(conn));
        }
        sqlite3_close(conn);
        return NULL;
    }
    /* should we register rand or power functions to the sqlite VM? */
    sql = apr_pcalloc(pool, sizeof(*sql));
    sql->conn = conn;
    sql->pool = pool;
    sql->trans = NULL;

    return sql;
}