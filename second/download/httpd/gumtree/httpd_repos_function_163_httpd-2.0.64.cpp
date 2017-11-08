static void dav_fs_close_lockdb(dav_lockdb *lockdb)
{
    if (lockdb->info->db != NULL)
	dav_dbm_close(lockdb->info->db);
}