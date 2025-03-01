static apr_status_t dbd_sqlite3_datum_get(const apr_dbd_row_t *row, int n,
                                          apr_dbd_type_e type, void *data)
{
    if ((n < 0) || ((size_t)n >= row->res->sz)) {
      return APR_EGENERAL;
    }

    if (row->columns[n]->type == SQLITE_NULL) {
        return APR_ENOENT;
    }

    switch (type) {
    case APR_DBD_TYPE_TINY:
        *(char*)data = atoi(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_UTINY:
        *(unsigned char*)data = atoi(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_SHORT:
        *(short*)data = atoi(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_USHORT:
        *(unsigned short*)data = atoi(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_INT:
        *(int*)data = atoi(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_UINT:
        *(unsigned int*)data = atoi(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_LONG:
        *(long*)data = atol(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_ULONG:
        *(unsigned long*)data = atol(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_LONGLONG:
        *(apr_int64_t*)data = apr_atoi64(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_ULONGLONG:
        *(apr_uint64_t*)data = apr_atoi64(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_FLOAT:
        *(float*)data = (float)atof(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_DOUBLE:
        *(double*)data = atof(row->columns[n]->value);
        break;
    case APR_DBD_TYPE_STRING:
    case APR_DBD_TYPE_TEXT:
    case APR_DBD_TYPE_TIME:
    case APR_DBD_TYPE_DATE:
    case APR_DBD_TYPE_DATETIME:
    case APR_DBD_TYPE_TIMESTAMP:
    case APR_DBD_TYPE_ZTIMESTAMP:
        *(char**)data = row->columns[n]->value;
        break;
    case APR_DBD_TYPE_BLOB:
    case APR_DBD_TYPE_CLOB:
        {
        apr_bucket *e;
        apr_bucket_brigade *b = (apr_bucket_brigade*)data;

        e = apr_bucket_pool_create(row->columns[n]->value,
                                   row->columns[n]->size,
                                   row->res->pool, b->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(b, e);
        }
        break;
    case APR_DBD_TYPE_NULL:
        *(void**)data = NULL;
        break;
    default:
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}