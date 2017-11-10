static void dbd_sqlite3_bind(apr_dbd_prepared_t *statement, const char **values)
{
    sqlite3_stmt *stmt = statement->stmt;
    int i, j;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        if (values[j] == NULL) {
            sqlite3_bind_null(stmt, i + 1);
        }
        else {
            switch (statement->types[i]) {
            case APR_DBD_TYPE_BLOB:
            case APR_DBD_TYPE_CLOB:
                {
                char *data = (char *)values[j];
                int size = atoi((char*)values[++j]);

                /* skip table and column */
                j += 2;

                sqlite3_bind_blob(stmt, i + 1, data, size, SQLITE_STATIC);
                }
                break;
            default:
                sqlite3_bind_text(stmt, i + 1, values[j],
                                  strlen(values[j]), SQLITE_STATIC);
                break;
            }
        }
    }

    return;
}