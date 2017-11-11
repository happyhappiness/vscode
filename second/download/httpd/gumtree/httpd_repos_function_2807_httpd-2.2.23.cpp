static apr_status_t odbc_parse_params(apr_pool_t *pool, const char *params,
                               int *connect, SQLCHAR **datasource, 
                               SQLCHAR **user, SQLCHAR **password, 
                               int *defaultBufferSize, int *nattrs,
                               int **attrs, int **attrvals)
{
    char *seps, *last, *next, *name[MAX_PARAMS], *val[MAX_PARAMS];
    int nparams = 0, i, j;

    *attrs = apr_pcalloc(pool, MAX_PARAMS * sizeof(char *));
    *attrvals = apr_pcalloc(pool, MAX_PARAMS * sizeof(int));
    *nattrs = 0;
    seps = DEFAULTSEPS;
    name[nparams] = apr_strtok(apr_pstrdup(pool, params), seps, &last);

    /* no params is OK here - let connect return a more useful error msg */
    if (!name[nparams])
        return SQL_SUCCESS;

    do {
        if (last[strspn(last, seps)] == CSINGLEQUOTE) {
            last += strspn(last, seps);
            seps=SSINGLEQUOTE;
        }
        val[nparams] = apr_strtok(NULL, seps, &last);
        seps = DEFAULTSEPS;

        ++nparams;
        next = apr_strtok(NULL, seps, &last);
        if (!next) {
            break;
        }
        if (nparams >= MAX_PARAMS) {
            /* too many parameters, no place to store */
            return APR_EGENERAL;
        }
        name[nparams] = next;
    } while (1);

    for (j = i = 0; i < nparams; i++) {
        if (!apr_strnatcasecmp(name[i], "CONNECT")) {
            *datasource = (SQLCHAR *)apr_pstrdup(pool, val[i]);
            *connect = 1;
        }
        else if (!apr_strnatcasecmp(name[i], "DATASOURCE")) {
            *datasource = (SQLCHAR *)apr_pstrdup(pool, val[i]);
            *connect = 0;
        }
        else if (!apr_strnatcasecmp(name[i], "USER")) {
            *user = (SQLCHAR *)apr_pstrdup(pool, val[i]);
        }
        else if (!apr_strnatcasecmp(name[i], "PASSWORD")) {
            *password = (SQLCHAR *)apr_pstrdup(pool, val[i]);
        }
        else if (!apr_strnatcasecmp(name[i], "BUFSIZE")) {
            *defaultBufferSize = atoi(val[i]);
        }
        else if (!apr_strnatcasecmp(name[i], "ACCESS")) {
            if (!apr_strnatcasecmp(val[i], "READ_ONLY"))
                (*attrvals)[j] = SQL_MODE_READ_ONLY;
            else if (!apr_strnatcasecmp(val[i], "READ_WRITE"))
                (*attrvals)[j] = SQL_MODE_READ_WRITE;
            else
                return SQL_ERROR;
            (*attrs)[j++] = SQL_ATTR_ACCESS_MODE;
        }
        else if (!apr_strnatcasecmp(name[i], "CTIMEOUT")) {
            (*attrvals)[j] = atoi(val[i]);
            (*attrs)[j++] = SQL_ATTR_LOGIN_TIMEOUT;
        }
        else if (!apr_strnatcasecmp(name[i], "STIMEOUT")) {
            (*attrvals)[j] = atoi(val[i]);
            (*attrs)[j++] = SQL_ATTR_CONNECTION_TIMEOUT;
        }
        else if (!apr_strnatcasecmp(name[i], "TXMODE")) {
            if (!apr_strnatcasecmp(val[i], "READ_UNCOMMITTED"))
                (*attrvals)[j] = SQL_TXN_READ_UNCOMMITTED;
            else if (!apr_strnatcasecmp(val[i], "READ_COMMITTED"))
                (*attrvals)[j] = SQL_TXN_READ_COMMITTED;
            else if (!apr_strnatcasecmp(val[i], "REPEATABLE_READ"))
                (*attrvals)[j] = SQL_TXN_REPEATABLE_READ;
            else if (!apr_strnatcasecmp(val[i], "SERIALIZABLE"))
                (*attrvals)[j] = SQL_TXN_SERIALIZABLE;
            else if (!apr_strnatcasecmp(val[i], "DEFAULT"))
                continue;
            else
                return SQL_ERROR;
            (*attrs)[j++] = SQL_ATTR_TXN_ISOLATION;
        }
        else
            return SQL_ERROR;
    }
    *nattrs = j;
    return (*datasource && *defaultBufferSize) ? APR_SUCCESS : SQL_ERROR;
}