static int dbd_mysql_pselect_internal(apr_pool_t *pool, apr_dbd_t *sql,
                                      apr_dbd_results_t **res,
                                      apr_dbd_prepared_t *statement,
                                      int random, MYSQL_BIND *bind)
{
    int nfields, i;
    my_bool *is_nullr;
#if MYSQL_VERSION_ID >= 50000
    my_bool *error;
#endif
    int ret;
    unsigned long *length, maxlen;

    ret = mysql_stmt_bind_param(statement->stmt, bind);
    if (ret == 0) {
        ret = mysql_stmt_execute(statement->stmt);
        if (!ret) {
            if (!*res) {
                *res = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
            }
            (*res)->random = random;
            (*res)->statement = statement->stmt;
            (*res)->res = mysql_stmt_result_metadata(statement->stmt);
            (*res)->pool = pool;
            apr_pool_cleanup_register(pool, (*res)->res,
                                      free_result, apr_pool_cleanup_null);
            nfields = mysql_num_fields((*res)->res);
            if (!(*res)->bind) {
                (*res)->bind = apr_palloc(pool, nfields*sizeof(MYSQL_BIND));
                length = apr_pcalloc(pool, nfields*sizeof(unsigned long));
#if MYSQL_VERSION_ID >= 50000
                error = apr_palloc(pool, nfields*sizeof(my_bool));
#endif
                is_nullr = apr_pcalloc(pool, nfields*sizeof(my_bool));
                for ( i = 0; i < nfields; ++i ) {
                    maxlen = ((*res)->res->fields[i].length < sql->fldsz ?
                              (*res)->res->fields[i].length : sql->fldsz) + 1;
                    if ((*res)->res->fields[i].type == MYSQL_TYPE_BLOB) {
                        (*res)->bind[i].buffer_type = MYSQL_TYPE_LONG_BLOB;
                    }
                    else {
                        (*res)->bind[i].buffer_type = MYSQL_TYPE_VAR_STRING;
                    }
                    (*res)->bind[i].buffer_length = maxlen;
                    (*res)->bind[i].length = &length[i];
                    (*res)->bind[i].buffer = apr_palloc(pool, maxlen);
                    (*res)->bind[i].is_null = is_nullr+i;
#if MYSQL_VERSION_ID >= 50000
                    (*res)->bind[i].error = error+i;
#endif
                }
            }
            ret = mysql_stmt_bind_result(statement->stmt, (*res)->bind);
            if (!ret) {
                ret = mysql_stmt_store_result(statement->stmt);
            }
        }
    }
    if (ret != 0) {
        ret = mysql_stmt_errno(statement->stmt);
    }

    return ret;
}