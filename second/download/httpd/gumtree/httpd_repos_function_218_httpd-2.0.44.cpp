void dav_fs_ensure_state_dir(apr_pool_t * p, const char *dirname)
{
    const char *pathname = apr_pstrcat(p, dirname, "/" DAV_FS_STATE_DIR, NULL);

    /* ### do we need to deal with the umask? */

    /* just try to make it, ignoring any resulting errors */
    (void) apr_dir_make(pathname, APR_OS_DEFAULT, p);
}