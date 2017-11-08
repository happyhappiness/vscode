static const char *dbd_sqlite_error(apr_dbd_t * sql, int n)
{
    return sql->errmsg;
}