static dav_error * dav_fs_really_open_lockdb(dav_lockdb *lockdb)
{
    dav_error *err;

    if (lockdb->info->opened)
        return NULL;

    err = dav_dbm_open_direct(lockdb->info->pool,
                              lockdb->info->lockdb_path,
                              lockdb->ro,
                              &lockdb->info->db);
    if (err != NULL) {
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