static dav_error * dav_dbm_open(apr_pool_t * p, const dav_resource *resource,
                                int ro, dav_db **pdb)
{
    const char *dirpath;
    const char *fname;
    const char *pathname;

    /* Get directory and filename for resource */
    /* ### should test this result value... */
    (void) dav_fs_dir_file_name(resource, &dirpath, &fname);

    /* If not opening read-only, ensure the state dir exists */
    if (!ro) {
        /* ### what are the perf implications of always checking this? */
        dav_fs_ensure_state_dir(p, dirpath);
    }

    pathname = apr_pstrcat(p, dirpath, "/" DAV_FS_STATE_DIR "/",
                              fname ? fname : DAV_FS_STATE_FILE_FOR_DIR,
                              NULL);

    /* ### readers cannot open while a writer has this open; we should
       ### perform a few retries with random pauses. */

    /* ### do we need to deal with the umask? */

    return dav_dbm_open_direct(p, pathname, ro, pdb);
}