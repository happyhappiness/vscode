static const char *dbd_pgsql_error(apr_dbd_t *sql, int n)
{
    return PQerrorMessage(sql->conn);
}