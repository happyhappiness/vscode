static apr_status_t vt_db_open(apr_dbm_t **pdb, const char *pathname,
                               apr_int32_t mode, apr_fileperms_t perm,
                               apr_pool_t *pool)
{
    real_file_t file;
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
        int dberr;

#if DB_VER >= 3
        if ((dberr = db_create(&file.bdb, NULL, 0)) == 0) {
            if ((dberr = (*file.bdb->open)(file.bdb,
#if DB_VER == 4
                                           NULL,
#endif
                                           pathname, NULL, 
                                           DB_HASH, dbmode, 
                                           apr_posix_perms2mode(perm))) != 0) {
                /* close the DB handler */
                (void) (*file.bdb->close)(file.bdb, 0);
            }
        }
        file.curs = NULL;
#elif DB_VER == 2
        dberr = db_open(pathname, DB_HASH, dbmode, apr_posix_perms2mode(perm),
                        NULL, NULL, &file.bdb);
        file.curs = NULL;
#else
        file.bdb = dbopen(pathname, dbmode, apr_posix_perms2mode(perm),
                          DB_HASH, NULL);
        if (file.bdb == NULL)
            return APR_EGENERAL;      /* ### need a better error */
        dberr = 0;
#endif
        if (dberr != 0)
            return db2s(dberr);
    }

    /* we have an open database... return it */
    *pdb = apr_pcalloc(pool, sizeof(**pdb));
    (*pdb)->pool = pool;
    (*pdb)->type = &apr_dbm_type_db;
    (*pdb)->file = apr_pmemdup(pool, &file, sizeof(file));

    /* ### register a cleanup to close the DBM? */

    return APR_SUCCESS;
}