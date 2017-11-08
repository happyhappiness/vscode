static int dbd_mysql_pvquery(apr_pool_t *pool, apr_dbd_t *sql, int *nrows,
                             apr_dbd_prepared_t *statement, va_list args)
{
    MYSQL_BIND *bind;
    char *arg;
    int ret;
    int nargs = 0;
    int i;
    my_bool is_null = FALSE;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }
    nargs = mysql_stmt_param_count(statement->stmt);

    bind = apr_palloc(pool, nargs*sizeof(MYSQL_BIND));
    for (i=0; i < nargs; ++i) {
        arg = va_arg(args, char*);
        bind[i].buffer_type = MYSQL_TYPE_VAR_STRING;
        bind[i].buffer = arg;
        bind[i].buffer_length = strlen(arg);
        bind[i].length = &bind[i].buffer_length;
        bind[i].is_null = &is_null;
        bind[i].is_unsigned = 0;
    }

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
        *nrows = mysql_stmt_affected_rows(statement->stmt);
    }
    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}