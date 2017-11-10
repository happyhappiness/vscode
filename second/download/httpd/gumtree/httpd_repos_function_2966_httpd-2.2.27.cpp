static void dbd_pgsql_bbind(apr_pool_t *pool, apr_dbd_prepared_t * statement,
                            const void **values,
                            const char **val, int *len, int *fmt)
{
    int i, j;
    apr_dbd_type_e type;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        type = (values[j] == NULL ? APR_DBD_TYPE_NULL : statement->types[i]);

        switch (type) {
        case APR_DBD_TYPE_TINY:
            val[i] = apr_itoa(pool, *(char*)values[j]);
            break;
        case APR_DBD_TYPE_UTINY:
            val[i] = apr_itoa(pool, *(unsigned char*)values[j]);
            break;
        case APR_DBD_TYPE_SHORT:
            val[i] = apr_itoa(pool, *(short*)values[j]);
            break;
        case APR_DBD_TYPE_USHORT:
            val[i] = apr_itoa(pool, *(unsigned short*)values[j]);
            break;
        case APR_DBD_TYPE_INT:
            val[i] = apr_itoa(pool, *(int*)values[j]);
            break;
        case APR_DBD_TYPE_UINT:
            val[i] = apr_itoa(pool, *(unsigned int*)values[j]);
            break;
        case APR_DBD_TYPE_LONG:
            val[i] = apr_ltoa(pool, *(long*)values[j]);
            break;
        case APR_DBD_TYPE_ULONG:
            val[i] = apr_ltoa(pool, *(unsigned long*)values[j]);
            break;
        case APR_DBD_TYPE_LONGLONG:
            val[i] = apr_psprintf(pool, "%" APR_INT64_T_FMT,
                                  *(apr_int64_t*)values[j]);
            break;
        case APR_DBD_TYPE_ULONGLONG:
            val[i] = apr_psprintf(pool, "%" APR_UINT64_T_FMT,
                                  *(apr_uint64_t*)values[j]);
            break;
        case APR_DBD_TYPE_FLOAT:
            val[i] = apr_psprintf(pool, "%f", *(float*)values[j]);
            break;
        case APR_DBD_TYPE_DOUBLE:
            val[i] = apr_psprintf(pool, "%lf", *(double*)values[j]);
            break;
        case APR_DBD_TYPE_STRING:
        case APR_DBD_TYPE_TEXT:
        case APR_DBD_TYPE_TIME:
        case APR_DBD_TYPE_DATE:
        case APR_DBD_TYPE_DATETIME:
        case APR_DBD_TYPE_TIMESTAMP:
        case APR_DBD_TYPE_ZTIMESTAMP:
            val[i] = values[j];
            break;
        case APR_DBD_TYPE_BLOB:
        case APR_DBD_TYPE_CLOB:
            val[i] = (char*)values[j];
            len[i] = *(apr_size_t*)values[++j];
            fmt[i] = 1;

            /* skip table and column */
            j += 2;
            break;
        case APR_DBD_TYPE_NULL:
        default:
            val[i] = NULL;
            break;
        }
    }

    return;
}