static apr_status_t htdbm_open(htdbm_t *htdbm)
{
    if (htdbm->create)
        return apr_dbm_open_ex(&htdbm->dbm, htdbm->type, htdbm->filename, APR_DBM_RWCREATE,
                            APR_OS_DEFAULT, htdbm->ctx.pool);
    else
        return apr_dbm_open_ex(&htdbm->dbm, htdbm->type, htdbm->filename,
                            htdbm->rdonly ? APR_DBM_READONLY : APR_DBM_READWRITE,
                            APR_OS_DEFAULT, htdbm->ctx.pool);
}