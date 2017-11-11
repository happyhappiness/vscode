static void dbd_mysql_bind(apr_dbd_prepared_t *statement,
                           const char **values, MYSQL_BIND *bind)
{
    int i, j;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        bind[i].length = &bind[i].buffer_length;
        bind[i].is_unsigned = 0;
        bind[i].is_null = NULL;

        if (values[j] == NULL) {
            bind[i].buffer_type = MYSQL_TYPE_NULL;
        }
        else {
            switch (statement->types[i]) {
            case APR_DBD_TYPE_BLOB:
            case APR_DBD_TYPE_CLOB:
                bind[i].buffer_type = MYSQL_TYPE_LONG_BLOB;
                bind[i].buffer = (void*)values[j];
                bind[i].buffer_length = atol(values[++j]);

                /* skip table and column */
                j += 2;
                break;
            default:
                bind[i].buffer_type = MYSQL_TYPE_VAR_STRING;
                bind[i].buffer = (void*)values[j];
                bind[i].buffer_length = strlen(values[j]);
                break;
            }
        }
    }

    return;
}