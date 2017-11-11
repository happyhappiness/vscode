static apr_status_t vt_ndbm_open(apr_dbm_t **pdb, const char *pathname,
                                 apr_int32_t mode, apr_fileperms_t perm,
                                 apr_pool_t *pool)
{
    DBM *file;
    int dbmode;

    *pdb = NULL;

    switch (mode) {
    case APR_DBM_READONLY:
        dbmode = APR_DBM_DBMODE_RO;
        break;
    case APR_DBM_READWRITE:
        dbmode = APR_DBM_DBMODE_RW;
        break;
    case APR_DBM_RWCREATE:
        dbmode = APR_DBM_DBMODE_RWCREATE;
        break;
    case APR_DBM_RWTRUNC:
        dbmode = APR_DBM_DBMODE_RWTRUNC;
        break;
    default:
        return APR_EINVAL;
    }

    {
        file = dbm_open(pathname, dbmode, apr_posix_perms2mode(perm));
        if (file == NULL)
            return APR_EGENERAL;      /* ### need a better error */
    }

    /* we have an open database... return it */
    *pdb = apr_pcalloc(pool, sizeof(**pdb));
    (*pdb)->pool = pool;
    (*pdb)->type = &apr_dbm_type_ndbm;
    (*pdb)->file = file;

    /* ### register a cleanup to close the DBM? */

    return APR_SUCCESS;
}