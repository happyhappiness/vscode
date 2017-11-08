static apr_status_t htdbm_verify(htdbm_t *htdbm)
{
    apr_datum_t key, val;
    char *pwd;
    char *rec, *cmnt;

    key.dptr = htdbm->username;
    key.dsize = strlen(htdbm->username);
    if (!apr_dbm_exists(htdbm->dbm, key))
        return APR_ENOENT;
    if (apr_dbm_fetch(htdbm->dbm, key, &val) != APR_SUCCESS)
        return APR_ENOENT;
    rec = apr_pstrndup(htdbm->ctx.pool, val.dptr, val.dsize);
    cmnt = strchr(rec, ':');
    if (cmnt)
        pwd = apr_pstrndup(htdbm->ctx.pool, rec, cmnt - rec);
    else
        pwd = apr_pstrdup(htdbm->ctx.pool, rec);
    return apr_password_validate(htdbm->ctx.passwd, pwd);
}