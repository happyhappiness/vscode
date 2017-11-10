static void dbd_oracle_bind(apr_dbd_prepared_t *statement, const char **values)
{
    OCIStmt *stmt = statement->stmt;
    apr_dbd_t *sql = statement->handle;
    int i, j;
    sb2 null_ind = -1;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        if (values[j] == NULL) {
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       NULL, 0, SQLT_STR,
                                       &null_ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
        }
        else {
            switch (statement->args[i].type) {
            case APR_DBD_TYPE_BLOB:
                {
                char *data = (char *)values[j];
                int size = atoi((char*)values[++j]);

                /* skip table and column for now */
                j += 2;

                sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                           sql->err, i + 1,
                                           data, size, SQLT_LBI,
                                           &statement->args[i].ind,
                                           NULL,
                                           (ub2) 0, (ub4) 0,
                                           (ub4 *) 0, OCI_DEFAULT);
                }
                break;
            case APR_DBD_TYPE_CLOB:
                {
                char *data = (char *)values[j];
                int size = atoi((char*)values[++j]);

                /* skip table and column for now */
                j += 2;

                sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                           sql->err, i + 1,
                                           data, size, SQLT_LNG,
                                           &statement->args[i].ind,
                                           NULL,
                                           (ub2) 0, (ub4) 0,
                                           (ub4 *) 0, OCI_DEFAULT);
                }
                break;
            default:
                sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                           sql->err, i + 1,
                                           (dvoid*) values[j],
                                           strlen(values[j]) + 1,
                                           SQLT_STR,
                                           &statement->args[i].ind,
                                           NULL,
                                           (ub2) 0, (ub4) 0,
                                           (ub4 *) 0, OCI_DEFAULT);
                break;
            }
        }

        if (sql->status != OCI_SUCCESS) {
            return;
        }
    }

    return;
}