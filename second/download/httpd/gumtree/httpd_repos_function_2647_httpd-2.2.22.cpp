static apr_status_t prep(apr_sdbm_t **pdb, const char *dirname, const char *pagname,
                         apr_int32_t flags, apr_fileperms_t perms, apr_pool_t *p)
{
    apr_sdbm_t *db;
    apr_status_t status;

    *pdb = NULL;

    db = malloc(sizeof(*db));
    memset(db, 0, sizeof(*db));

    db->pool = p;

    /*
     * adjust user flags so that WRONLY becomes RDWR, 
     * as required by this package. Also set our internal
     * flag for RDONLY if needed.
     */
    if (!(flags & APR_FOPEN_WRITE)) {
        db->flags |= SDBM_RDONLY;
    }

    /*
     * adjust the file open flags so that we handle locking
     * on our own (don't rely on any locking behavior within
     * an apr_file_t, in case it's ever introduced, and set
     * our own flag.
     */
    if (flags & APR_FOPEN_SHARELOCK) {
        db->flags |= SDBM_SHARED;
        flags &= ~APR_FOPEN_SHARELOCK;
    }

    flags |= APR_FOPEN_BINARY | APR_FOPEN_READ;

    /*
     * open the files in sequence, and stat the dirfile.
     * If we fail anywhere, undo everything, return NULL.
     */

    if ((status = apr_file_open(&db->dirf, dirname, flags, perms, p))
                != APR_SUCCESS)
        goto error;

    if ((status = apr_file_open(&db->pagf, pagname, flags, perms, p))
                != APR_SUCCESS)
        goto error;

    if ((status = apr_sdbm_lock(db, (db->flags & SDBM_RDONLY) 
                                        ? APR_FLOCK_SHARED
                                        : APR_FLOCK_EXCLUSIVE))
                != APR_SUCCESS)
        goto error;

    /* apr_pcalloc zeroed the buffers
     * apr_sdbm_lock stated the dirf->size and invalidated the cache
     */

    /*
     * if we are opened in SHARED mode, unlock ourself 
     */
    if (db->flags & SDBM_SHARED)
        if ((status = apr_sdbm_unlock(db)) != APR_SUCCESS)
            goto error;

    /* make sure that we close the database at some point */
    apr_pool_cleanup_register(p, db, database_cleanup, apr_pool_cleanup_null);

    /* Done! */
    *pdb = db;
    return APR_SUCCESS;

error:
    if (db->dirf && db->pagf)
        (void) apr_sdbm_unlock(db);
    if (db->dirf != NULL)
        (void) apr_file_close(db->dirf);
    if (db->pagf != NULL) {
        (void) apr_file_close(db->pagf);
    }
    free(db);
    return status;
}