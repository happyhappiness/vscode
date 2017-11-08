static apr_status_t htdbm_del(htdbm_t *htdbm) 
{
    apr_datum_t key;

    key.dptr = htdbm->username;
    key.dsize = strlen(htdbm->username);
    if (!apr_dbm_exists(htdbm->dbm, key))
        return APR_ENOENT;

    return apr_dbm_delete(htdbm->dbm, key);
}