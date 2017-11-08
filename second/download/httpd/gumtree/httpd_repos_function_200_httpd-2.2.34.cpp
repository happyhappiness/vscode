static dav_error * dav_fs_open_lockdb(request_rec *r, int ro, int force,
                                      dav_lockdb **lockdb)
{
    dav_lockdb_combined *comb;

    comb = apr_pcalloc(r->pool, sizeof(*comb));
    comb->pub.hooks = &dav_hooks_locks_fs;
    comb->pub.ro = ro;
    comb->pub.info = &comb->priv;
    comb->priv.r = r;
    comb->priv.pool = r->pool;

    comb->priv.lockdb_path = dav_get_lockdb_path(r);
    if (comb->priv.lockdb_path == NULL) {
        return dav_new_error(r->pool, HTTP_INTERNAL_SERVER_ERROR,
                             DAV_ERR_LOCK_NO_DB,
                             "A lock database was not specified with the "
                             "DAVLockDB directive. One must be specified "
                             "to use the locking functionality.");
    }

    /* done initializing. return it. */
    *lockdb = &comb->pub;

    if (force) {
        /* ### add a higher-level comment? */
        return dav_fs_really_open_lockdb(*lockdb);
    }

    return NULL;
}