static void dbd_oracle_bbind(apr_dbd_prepared_t * statement,
                             const void **values)
{
    OCIStmt *stmt = statement->stmt;
    apr_dbd_t *sql = statement->handle;
    int i, j;
    sb2 null_ind = -1;
    apr_dbd_type_e type;

    for (i = 0, j = 0; i < statement->nargs; i++, j++) {
        type = (values[j] == NULL ? APR_DBD_TYPE_NULL
                                  : statement->args[i].type);

        switch (type) {
        case APR_DBD_TYPE_TINY:
            statement->args[i].value.ival = *(char*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.ival,
                                       sizeof(statement->args[i].value.ival),
                                       SQLT_INT,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_UTINY:
            statement->args[i].value.uval = *(unsigned char*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.uval,
                                       sizeof(statement->args[i].value.uval),
                                       SQLT_UIN,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_SHORT:
            statement->args[i].value.ival = *(short*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.ival,
                                       sizeof(statement->args[i].value.ival),
                                       SQLT_INT,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_USHORT:
            statement->args[i].value.uval = *(unsigned short*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.uval,
                                       sizeof(statement->args[i].value.uval),
                                       SQLT_UIN,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_INT:
            statement->args[i].value.ival = *(int*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.ival,
                                       sizeof(statement->args[i].value.ival),
                                       SQLT_INT,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_UINT:
            statement->args[i].value.uval = *(unsigned int*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.uval,
                                       sizeof(statement->args[i].value.uval),
                                       SQLT_UIN,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_LONG:
            statement->args[i].value.sval =
                apr_psprintf(statement->pool, "%ld", *(long*)values[j]);
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       statement->args[i].value.sval,
                                       strlen(statement->args[i].value.sval)+1,
                                       SQLT_STR,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_ULONG:
            statement->args[i].value.sval =
                apr_psprintf(statement->pool, "%lu",
                                              *(unsigned long*)values[j]);
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       statement->args[i].value.sval,
                                       strlen(statement->args[i].value.sval)+1,
                                       SQLT_STR,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_LONGLONG:
            statement->args[i].value.sval =
                apr_psprintf(statement->pool, "%" APR_INT64_T_FMT,
                                              *(apr_int64_t*)values[j]);
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       statement->args[i].value.sval,
                                       strlen(statement->args[i].value.sval)+1,
                                       SQLT_STR,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_ULONGLONG:
            statement->args[i].value.sval =
                apr_psprintf(statement->pool, "%" APR_UINT64_T_FMT,
                                              *(apr_uint64_t*)values[j]);
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       statement->args[i].value.sval,
                                       strlen(statement->args[i].value.sval)+1,
                                       SQLT_UIN,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_FLOAT:
            statement->args[i].value.fval = *(float*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.fval,
                                       sizeof(statement->args[i].value.fval),
                                       SQLT_FLT,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_DOUBLE:
            statement->args[i].value.fval = *(double*)values[j];
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       &statement->args[i].value.fval,
                                       sizeof(statement->args[i].value.fval),
                                       SQLT_FLT,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_STRING:
        case APR_DBD_TYPE_TEXT:
        case APR_DBD_TYPE_TIME:
        case APR_DBD_TYPE_DATE:
        case APR_DBD_TYPE_DATETIME:
        case APR_DBD_TYPE_TIMESTAMP:
        case APR_DBD_TYPE_ZTIMESTAMP:
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       (dvoid*) values[j],
                                       strlen(values[j]) + 1,
                                       SQLT_STR,
                                       &statement->args[i].ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        case APR_DBD_TYPE_BLOB:
            {
            char *data = (char *)values[j];
            apr_size_t size = *(apr_size_t*)values[++j];

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
            apr_size_t size = *(apr_size_t*)values[++j];

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
        case APR_DBD_TYPE_NULL:
        default:
            sql->status = OCIBindByPos(stmt, &statement->args[i].bind,
                                       sql->err, i + 1,
                                       NULL, 0, SQLT_STR,
                                       &null_ind, NULL,
                                       (ub2) 0, (ub4) 0,
                                       (ub4 *) 0, OCI_DEFAULT);
            break;
        }

        if (sql->status != OCI_SUCCESS) {
            return;
        }
    }

    return;
}