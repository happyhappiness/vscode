static apr_dbd_t *dbd_sqlite_open(apr_pool_t * pool, const char *params_)
{
    apr_dbd_t *sql;
    sqlite *conn = NULL;
    char *filename, *perm;
    int iperms = 600;
    char* params = apr_pstrdup(pool, params_);
    /* params = "[filename]:[permissions]"
     *    example: "shopping.db:600"
     */

    perm = strstr(params, ":");
    if (perm) {
        *(perm++) = '\x00';     // split the filename and permissions

        if (strlen(perm) > 0)
            iperms = atoi(perm);
    }

    conn = sqlite_open(params, iperms, NULL);

    sql = apr_pcalloc(pool, sizeof(*sql));
    sql->conn = conn;

    return sql;
}