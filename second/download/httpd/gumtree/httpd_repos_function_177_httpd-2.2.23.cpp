static dav_error * dav_generic_really_open_lockdb(dav_lockdb *lockdb)
{
    dav_error *err;
    apr_status_t status;

    if (lockdb->info->opened) {
        return NULL;
    }

    status = apr_dbm_open(&lockdb->info->db, lockdb->info->lockdb_path,
                          lockdb->ro ? APR_DBM_READONLY : APR_DBM_RWCREATE,
                          APR_OS_DEFAULT, lockdb->info->pool);

    if (status) {
        err = dav_generic_dbm_new_error(lockdb->info->db, lockdb->info->pool,
                                        status);
        return dav_push_error(lockdb->info->pool,
                              HTTP_INTERNAL_SERVER_ERROR,
                              DAV_ERR_LOCK_OPENDB,
                              "Could not open the lock database.",
                              err);
    }

    /* all right. it is opened now. */
    lockdb->info->opened = 1;

    return NULL;
}