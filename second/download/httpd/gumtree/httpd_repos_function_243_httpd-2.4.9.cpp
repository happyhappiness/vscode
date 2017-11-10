static dav_error *dav_fs_deleteset(apr_pool_t *p, const dav_resource *resource)
{
    const char *dirpath;
    const char *fname;
    const char *state1;
    const char *state2;
    const char *pathname;
    apr_status_t status;

    /* Get directory, filename, and state-file names for the resource */
    /* ### should test this result value... */
    (void) dav_fs_dir_file_name(resource, &dirpath, &fname);
    dav_dbm_get_statefiles(p, fname, &state1, &state2);

    /* build the propset pathname for the file */
    pathname = apr_pstrcat(p,
                          dirpath,
                          "/" DAV_FS_STATE_DIR "/",
                          state1,
                          NULL);

    /* note: we may get ENOENT if the state dir is not present */
    if ((status = apr_file_remove(pathname, p)) != APR_SUCCESS
        && !APR_STATUS_IS_ENOENT(status)) {
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                             "Could not remove properties.");
    }

    if (state2 != NULL) {
        /* build the propset pathname for the file */
        pathname = apr_pstrcat(p,
                              dirpath,
                              "/" DAV_FS_STATE_DIR "/",
                              state2,
                              NULL);

        if ((status = apr_file_remove(pathname, p)) != APR_SUCCESS
            && !APR_STATUS_IS_ENOENT(status)) {
            /* ### CRAP. only removed half. */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                                 "Could not fully remove properties. "
                                 "The server is now in an inconsistent "
                                 "state.");
        }
    }

    return NULL;
}