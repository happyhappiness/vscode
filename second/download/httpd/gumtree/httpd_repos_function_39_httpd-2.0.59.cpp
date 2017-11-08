static apr_status_t htdbm_save(htdbm_t *htdbm, int *changed) 
{
    apr_datum_t key, val;

    if (!htdbm->username)
        return APR_SUCCESS;

    key.dptr = htdbm->username;
    key.dsize = strlen(htdbm->username);
    if (apr_dbm_exists(htdbm->dbm, key))
        *changed = 1;

    val.dsize = strlen(htdbm->userpass);
    if (!htdbm->comment)
        val.dptr  = htdbm->userpass;
    else {
        val.dptr = apr_pstrcat(htdbm->pool, htdbm->userpass, ":",
                               htdbm->comment, NULL);
        val.dsize += (strlen(htdbm->comment) + 1);
    }
    return apr_dbm_store(htdbm->dbm, key, val);
}