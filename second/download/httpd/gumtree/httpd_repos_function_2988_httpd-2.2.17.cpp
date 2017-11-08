static int dbd_mysql_pquery_internal(apr_pool_t *pool, apr_dbd_t *sql,
                                     int *nrows, apr_dbd_prepared_t *statement,
                                     MYSQL_BIND *bind)
{
    int ret;

    ret = mysql_stmt_bind_param(statement->stmt, bind);
    if (ret != 0) {
        *nrows = 0;
        ret = mysql_stmt_errno(statement->stmt);
    }
    else {
        ret = mysql_stmt_execute(statement->stmt);
        if (ret != 0) {
            ret = mysql_stmt_errno(statement->stmt);
        }
        *nrows = (int) mysql_stmt_affected_rows(statement->stmt);
    }

    return ret;
}