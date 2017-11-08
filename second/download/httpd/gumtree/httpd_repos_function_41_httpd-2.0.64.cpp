static apr_status_t htdbm_verify(htdbm_t *htdbm) 
{
    apr_datum_t key, val;
    char pwd[MAX_STRING_LEN] = {0};
    char *rec, *cmnt;

    key.dptr = htdbm->username;
    key.dsize = strlen(htdbm->username);
    if (!apr_dbm_exists(htdbm->dbm, key))
        return APR_ENOENT;    
    if (apr_dbm_fetch(htdbm->dbm, key, &val) != APR_SUCCESS)
        return APR_ENOENT;
    rec = apr_pstrndup(htdbm->pool, val.dptr, val.dsize);
    cmnt = strchr(rec, ';');
    if (cmnt)
        strncpy(pwd, rec, cmnt - rec);
    else
        strcpy(pwd, rec);
    return apr_password_validate(htdbm->userpass, pwd);
}