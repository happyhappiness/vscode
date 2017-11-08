static void dav_generic_close_lockdb(dav_lockdb *lockdb)
{
    if (lockdb->info->db != NULL) {
        apr_dbm_close(lockdb->info->db);
    }
    lockdb->info->opened = 0;
}