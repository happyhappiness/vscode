static apr_status_t database_cleanup(void *data)
{
    apr_sdbm_t *db = data;

    /*
     * Can't rely on apr_sdbm_unlock, since it will merely
     * decrement the refcnt if several locks are held.
     */
    if (db->flags & (SDBM_SHARED_LOCK | SDBM_EXCLUSIVE_LOCK))
        (void) apr_file_unlock(db->dirf);
    (void) apr_file_close(db->dirf);
    (void) apr_file_close(db->pagf);
    free(db);

    return APR_SUCCESS;
}