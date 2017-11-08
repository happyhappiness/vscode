static const char *dbd_sqlite3_error(apr_dbd_t *sql, int n)
{
    return sqlite3_errmsg(sql->conn);
}