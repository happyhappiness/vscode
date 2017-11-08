dav_error * dav_dbm_open_direct(apr_pool_t *p, const char *pathname, int ro,
                                dav_db **pdb)
{
    apr_status_t status;
    apr_dbm_t *file;

    *pdb = NULL;

    if ((status = apr_dbm_open(&file, pathname,
                               ro ? APR_DBM_READONLY : APR_DBM_RWCREATE, 
                               APR_OS_DEFAULT, p))
                != APR_SUCCESS
        && !ro) {
        /* ### do something with 'status' */

        /* we can't continue if we couldn't open the file 
           and we need to write */
        return dav_fs_dbm_error(NULL, p, status);
    }

    /* may be NULL if we tried to open a non-existent db as read-only */
    if (file != NULL) {
        /* we have an open database... return it */
        *pdb = apr_pcalloc(p, sizeof(**pdb));
        (*pdb)->pool = p;
        (*pdb)->file = file;
    }

    return NULL;
}