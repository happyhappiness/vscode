static void dbd_pgsql_bind(apr_dbd_prepared_t *statement,
                           const char **values,
                           const char **val, int *len, int *fmt)
{
    int i, j;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        if (values[j] == NULL) {
            val[i] = NULL;
        }
        else {
            switch (statement->types[i]) {
            case APR_DBD_TYPE_BLOB:
            case APR_DBD_TYPE_CLOB:
                val[i] = (char *)values[j];
                len[i] = atoi(values[++j]);
                fmt[i] = 1;

                /* skip table and column */
                j += 2;
                break;
            default:
                val[i] = values[j];
                break;
            }
        }
    }

    return;
}