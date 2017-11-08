static void dbd_sqlite3_bbind(apr_dbd_prepared_t * statement,
                              const void **values)
{
    sqlite3_stmt *stmt = statement->stmt;
    int i, j;
    apr_dbd_type_e type;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        type = (values[j] == NULL ? APR_DBD_TYPE_NULL : statement->types[i]);

        switch (type) {
        case APR_DBD_TYPE_TINY:
            sqlite3_bind_int(stmt, i + 1, *(char*)values[j]);
            break;
        case APR_DBD_TYPE_UTINY:
            sqlite3_bind_int(stmt, i + 1, *(unsigned char*)values[j]);
            break;
        case APR_DBD_TYPE_SHORT:
            sqlite3_bind_int(stmt, i + 1, *(short*)values[j]);
            break;
        case APR_DBD_TYPE_USHORT:
            sqlite3_bind_int(stmt, i + 1, *(unsigned short*)values[j]);
            break;
        case APR_DBD_TYPE_INT:
            sqlite3_bind_int(stmt, i + 1, *(int*)values[j]);
            break;
        case APR_DBD_TYPE_UINT:
            sqlite3_bind_int(stmt, i + 1, *(unsigned int*)values[j]);
            break;
        case APR_DBD_TYPE_LONG:
            sqlite3_bind_int64(stmt, i + 1, *(long*)values[j]);
            break;
        case APR_DBD_TYPE_ULONG:
            sqlite3_bind_int64(stmt, i + 1, *(unsigned long*)values[j]);
            break;
        case APR_DBD_TYPE_LONGLONG:
            sqlite3_bind_int64(stmt, i + 1, *(apr_int64_t*)values[j]);
            break;
        case APR_DBD_TYPE_ULONGLONG:
            sqlite3_bind_int64(stmt, i + 1, *(apr_uint64_t*)values[j]);
            break;
        case APR_DBD_TYPE_FLOAT:
            sqlite3_bind_double(stmt, i + 1, *(float*)values[j]);
            break;
        case APR_DBD_TYPE_DOUBLE:
            sqlite3_bind_double(stmt, i + 1, *(double*)values[j]);
            break;
        case APR_DBD_TYPE_STRING:
        case APR_DBD_TYPE_TEXT:
        case APR_DBD_TYPE_TIME:
        case APR_DBD_TYPE_DATE:
        case APR_DBD_TYPE_DATETIME:
        case APR_DBD_TYPE_TIMESTAMP:
        case APR_DBD_TYPE_ZTIMESTAMP:
            sqlite3_bind_text(stmt, i + 1, values[j], strlen(values[j]),
                              SQLITE_STATIC);
            break;
        case APR_DBD_TYPE_BLOB:
        case APR_DBD_TYPE_CLOB:
            {
            char *data = (char*)values[j];
            apr_size_t size = *(apr_size_t*)values[++j];

            sqlite3_bind_blob(stmt, i + 1, data, size, SQLITE_STATIC);

            /* skip table and column */
            j += 2;
            }
            break;
        case APR_DBD_TYPE_NULL:
        default:
            sqlite3_bind_null(stmt, i + 1);
            break;
        }
    }

    return;
}