static int dbd_pgsql_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                             const char *query, const char *label,
                             apr_dbd_prepared_t **statement)
{
    char *sqlcmd;
    char *sqlptr;
    size_t length;
    size_t i = 0;
    const char *args[QUERY_MAX_ARGS];
    size_t alen;
    int nargs = 0;
    int ret;
    PGresult *res;
    char *pgquery;
    char *pgptr;

    if (!*statement) {
        *statement = apr_palloc(pool, sizeof(apr_dbd_prepared_t));
    }
    /* Translate from apr_dbd to native query format */
    for (sqlptr = (char*)query; *sqlptr; ++sqlptr) {
        if ((sqlptr[0] == '%') && isalpha(sqlptr[1])) {
            ++nargs;
        }
    }
    length = strlen(query) + 1;
    if (nargs > 8) {
        length += nargs - 8;
    }
    pgptr = pgquery = apr_palloc(pool, length) ;

    for (sqlptr = (char*)query; *sqlptr; ++sqlptr) {
        if ((sqlptr[0] == '%') && isalpha(sqlptr[1])) {
            *pgptr++ = '$';
            if (i < 9) {
                *pgptr++ = '1' + i;
            }
            else {
                *pgptr++ = '0' + ((i+1)/10);
                *pgptr++ = '0' + ((i+1)%10);
            }
            switch (*++sqlptr) {
            case 'd':
                args[i] = "integer";
                break;
            case 's':
                args[i] = "varchar";
                break;
            default:
                args[i] = "varchar";
                break;
            }
            length += 1 + strlen(args[i]);
            ++i;
        }
        else if ((sqlptr[0] == '%') && (sqlptr[1] == '%')) {
            /* reduce %% to % */
            *pgptr++ = *sqlptr++;
        }
        else {
            *pgptr++ = *sqlptr;
        }
    }
    *pgptr = 0;

    if (!label) {
        /* don't really prepare; use in execParams instead */
        (*statement)->prepared = 0;
        (*statement)->name = apr_pstrdup(pool, pgquery);
        return 0;
    }
    (*statement)->name = apr_pstrdup(pool, label);

    /* length of SQL query that prepares this statement */
    length = 8 + strlen(label) + 2 + 4 + length + 1;
    sqlcmd = apr_palloc(pool, length);
    sqlptr = sqlcmd;
    memcpy(sqlptr, "PREPARE ", 8);
    sqlptr += 8;
    length = strlen(label);
    memcpy(sqlptr, label, length);
    sqlptr += length;
    if (nargs > 0) {
        memcpy(sqlptr, " (",2);
        sqlptr += 2;
        for (i=0; i<nargs; ++i) {
            alen = strlen(args[i]);
            memcpy(sqlptr, args[i], alen);
            sqlptr += alen;
            *sqlptr++ = ',';
        }
        sqlptr[-1] =  ')';
    }
    memcpy(sqlptr, " AS ", 4);
    sqlptr += 4;
    memcpy(sqlptr, pgquery, strlen(pgquery));
    sqlptr += strlen(pgquery);
    *sqlptr = 0;

    res = PQexec(sql->conn, sqlcmd);
    if ( res ) {
        ret = PQresultStatus(res);
        if (dbd_pgsql_is_success(ret)) {
            ret = 0;
        }
        /* Hmmm, do we do this here or register it on the pool? */
        PQclear(res);
    }
    else {
        ret = PGRES_FATAL_ERROR;
    }
    (*statement)->prepared = 1;

    return ret;
}