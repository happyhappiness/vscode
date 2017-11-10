static void dbd_mysql_bbind(apr_pool_t *pool, apr_dbd_prepared_t *statement,
                            const void **values, MYSQL_BIND *bind)
{
    void *arg;
    int i, j;
    apr_dbd_type_e type;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        arg = (void *)values[j];

        bind[i].length = &bind[i].buffer_length;
        bind[i].is_null = NULL;

        type = (arg == NULL ? APR_DBD_TYPE_NULL : statement->types[i]);
        switch (type) {
        case APR_DBD_TYPE_TINY:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_TINY;
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_UTINY:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_TINY;
            bind[i].is_unsigned = 1;
            break;
        case APR_DBD_TYPE_SHORT:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_SHORT;
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_USHORT:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_SHORT;
            bind[i].is_unsigned = 1;
            break;
        case APR_DBD_TYPE_INT:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_LONG;
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_UINT:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_LONG;
            bind[i].is_unsigned = 1;
            break;
        case APR_DBD_TYPE_LONG:
            if (sizeof(int) == sizeof(long)) {
                bind[i].buffer = arg;
            }
            else {
                bind[i].buffer = apr_palloc(pool, sizeof(int));
                *(int*)bind[i].buffer = *(long*)arg;
            }
            bind[i].buffer_type = MYSQL_TYPE_LONG;
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_ULONG:
            if (sizeof(unsigned int) == sizeof(unsigned long)) {
                bind[i].buffer = arg;
            }
            else {
                bind[i].buffer = apr_palloc(pool, sizeof(unsigned int));
                *(unsigned int*)bind[i].buffer = *(unsigned long*)arg;
            }
            bind[i].buffer_type = MYSQL_TYPE_LONG;
            bind[i].is_unsigned = 1;
            break;
        case APR_DBD_TYPE_LONGLONG:
            if (sizeof(my_ulonglong) == sizeof(apr_int64_t)) {
                bind[i].buffer = arg;
                bind[i].buffer_type = MYSQL_TYPE_LONGLONG;
            }
            else { /* have to downsize, long long is not portable */
                bind[i].buffer = apr_palloc(pool, sizeof(long));
                *(long*)bind[i].buffer = (long) *(apr_int64_t*)arg;
                bind[i].buffer_type = MYSQL_TYPE_LONG;
            }
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_ULONGLONG:
            if (sizeof(my_ulonglong) == sizeof(apr_uint64_t)) {
                bind[i].buffer = arg;
                bind[i].buffer_type = MYSQL_TYPE_LONGLONG;
            }
            else { /* have to downsize, long long is not portable */
                bind[i].buffer = apr_palloc(pool, sizeof(long));
                *(unsigned long*)bind[i].buffer =
                    (unsigned long) *(apr_uint64_t*)arg;
                bind[i].buffer_type = MYSQL_TYPE_LONG;
            }
            bind[i].is_unsigned = 1;
            break;
        case APR_DBD_TYPE_FLOAT:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_FLOAT;
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_DOUBLE:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_DOUBLE;
            bind[i].is_unsigned = 0;
            break;
        case APR_DBD_TYPE_STRING:
        case APR_DBD_TYPE_TEXT:
        case APR_DBD_TYPE_TIME:
        case APR_DBD_TYPE_DATE:
        case APR_DBD_TYPE_DATETIME:
        case APR_DBD_TYPE_TIMESTAMP:
        case APR_DBD_TYPE_ZTIMESTAMP:
            bind[i].buffer = arg;
            bind[i].buffer_type = MYSQL_TYPE_VAR_STRING;
            bind[i].is_unsigned = 0;
            bind[i].buffer_length = strlen((const char *)arg);
            break;
        case APR_DBD_TYPE_BLOB:
        case APR_DBD_TYPE_CLOB:
            bind[i].buffer = (void *)arg;
            bind[i].buffer_type = MYSQL_TYPE_LONG_BLOB;
            bind[i].is_unsigned = 0;
            bind[i].buffer_length = *(apr_size_t*)values[++j];

            /* skip table and column */
            j += 2;
            break;
        case APR_DBD_TYPE_NULL:
        default:
            bind[i].buffer_type = MYSQL_TYPE_NULL;
            break;
        }
    }

    return;
}