void dav_dbm_get_statefiles(apr_pool_t *p, const char *fname,
                            const char **state1, const char **state2)
{
    if (fname == NULL)
        fname = DAV_FS_STATE_FILE_FOR_DIR;

    apr_dbm_get_usednames(p, fname, state1, state2);
}