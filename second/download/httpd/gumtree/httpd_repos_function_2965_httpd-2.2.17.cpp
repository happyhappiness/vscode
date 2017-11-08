static apr_dbd_t *dbd_pgsql_open(apr_pool_t *pool, const char *params,
                                 const char **error)
{
    apr_dbd_t *sql;
    
    PGconn *conn = PQconnectdb(params);

    /* if there's an error in the connect string or something we get
     * back a * bogus connection object, and things like PQreset are
     * liable to segfault, so just close it out now.  it would be nice
     * if we could give an indication of why we failed to connect... */
    if (PQstatus(conn) != CONNECTION_OK) {
        if (error) {
            *error = apr_pstrdup(pool, PQerrorMessage(conn));
        }
        PQfinish(conn);
        return NULL;
    }

    PQsetNoticeReceiver(conn, null_notice_receiver, NULL);
    PQsetNoticeProcessor(conn, null_notice_processor, NULL);

    sql = apr_pcalloc (pool, sizeof (*sql));

    sql->conn = conn;

    return sql;
}