static apr_status_t dbd_mysql_datum_get(const apr_dbd_row_t *row, int n,
                                        apr_dbd_type_e type, void *data)
{
    if (row->res->statement) {
        MYSQL_BIND *bind = &row->res->bind[n];
        unsigned long len = *bind->length;

        if (mysql_stmt_fetch_column(row->res->statement, bind, n, 0) != 0) {
            return APR_EGENERAL;
        }

        if (*bind->is_null) {
            return APR_ENOENT;
        }

        switch (type) {
        case APR_DBD_TYPE_TINY:
            *(char*)data = atoi(bind->buffer);
            break;
        case APR_DBD_TYPE_UTINY:
            *(unsigned char*)data = atoi(bind->buffer);
            break;
        case APR_DBD_TYPE_SHORT:
            *(short*)data = atoi(bind->buffer);
            break;
        case APR_DBD_TYPE_USHORT:
            *(unsigned short*)data = atoi(bind->buffer);
            break;
        case APR_DBD_TYPE_INT:
            *(int*)data = atoi(bind->buffer);
            break;
        case APR_DBD_TYPE_UINT:
            *(unsigned int*)data = atoi(bind->buffer);
            break;
        case APR_DBD_TYPE_LONG:
            *(long*)data = atol(bind->buffer);
            break;
        case APR_DBD_TYPE_ULONG:
            *(unsigned long*)data = atol(bind->buffer);
            break;
        case APR_DBD_TYPE_LONGLONG:
            *(apr_int64_t*)data = apr_atoi64(bind->buffer);
            break;
        case APR_DBD_TYPE_ULONGLONG:
            *(apr_uint64_t*)data = apr_atoi64(bind->buffer);
            break;
        case APR_DBD_TYPE_FLOAT:
            *(float*)data = (float) atof(bind->buffer);
            break;
        case APR_DBD_TYPE_DOUBLE:
            *(double*)data = atof(bind->buffer);
            break;
        case APR_DBD_TYPE_STRING:
        case APR_DBD_TYPE_TEXT:
        case APR_DBD_TYPE_TIME:
        case APR_DBD_TYPE_DATE:
        case APR_DBD_TYPE_DATETIME:
        case APR_DBD_TYPE_TIMESTAMP:
        case APR_DBD_TYPE_ZTIMESTAMP:
            *((char*)bind->buffer+bind->buffer_length-1) = '\0';
            *(char**)data = bind->buffer;
            break;
        case APR_DBD_TYPE_BLOB:
        case APR_DBD_TYPE_CLOB:
            {
            apr_bucket *e;
            apr_bucket_brigade *b = (apr_bucket_brigade*)data;

            e = apr_bucket_lob_create(row, n, 0, len,
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
    }
    else {
        if (row->row[n] == NULL) {
            return APR_ENOENT;
        }

        switch (type) {
        case APR_DBD_TYPE_TINY:
            *(char*)data = atoi(row->row[n]);
            break;
        case APR_DBD_TYPE_UTINY:
            *(unsigned char*)data = atoi(row->row[n]);
            break;
        case APR_DBD_TYPE_SHORT:
            *(short*)data = atoi(row->row[n]);
            break;
        case APR_DBD_TYPE_USHORT:
            *(unsigned short*)data = atoi(row->row[n]);
            break;
        case APR_DBD_TYPE_INT:
            *(int*)data = atoi(row->row[n]);
            break;
        case APR_DBD_TYPE_UINT:
            *(unsigned int*)data = atoi(row->row[n]);
            break;
        case APR_DBD_TYPE_LONG:
            *(long*)data = atol(row->row[n]);
            break;
        case APR_DBD_TYPE_ULONG:
            *(unsigned long*)data = atol(row->row[n]);
            break;
        case APR_DBD_TYPE_LONGLONG:
            *(apr_int64_t*)data = apr_atoi64(row->row[n]);
            break;
        case APR_DBD_TYPE_ULONGLONG:
            *(apr_uint64_t*)data = apr_atoi64(row->row[n]);
            break;
        case APR_DBD_TYPE_FLOAT:
            *(float*)data = (float) atof(row->row[n]);
            break;
        case APR_DBD_TYPE_DOUBLE:
            *(double*)data = atof(row->row[n]);
            break;
        case APR_DBD_TYPE_STRING:
        case APR_DBD_TYPE_TEXT:
        case APR_DBD_T