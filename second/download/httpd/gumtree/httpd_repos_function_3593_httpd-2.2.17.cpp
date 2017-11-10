apr_status_t apr_dir_open(apr_dir_t **new, const char *dirname, 
                          apr_pool_t *pool)
{
    /* On some platforms (e.g., Linux+GNU libc), d_name[] in struct 
     * dirent is declared with enough storage for the name.  On other
     * platforms (e.g., Solaris 8 for Intel), d_name is declared as a
     * one-byte array.  Note: gcc evaluates this at compile time.
     */
    apr_size_t dirent_size = 
        sizeof(*(*new)->entry) +
        (sizeof((*new)->entry->d_name) > 1 ? 0 : 255);
    DIR *dir = opendir(dirname);

    if (!dir) {
        return errno;
    }

    (*new) = (apr_dir_t *)apr_palloc(pool, sizeof(apr_dir_t));

    (*new)->pool = pool;
    (*new)->dirname = apr_pstrdup(pool, dirname);
    (*new)->dirstruct = dir;
    (*new)->entry = apr_pcalloc(pool, dirent_size);

    apr_pool_cleanup_register((*new)->pool, *new, dir_cleanup,
                              apr_pool_cleanup_null);
    return APR_SUCCESS;
}