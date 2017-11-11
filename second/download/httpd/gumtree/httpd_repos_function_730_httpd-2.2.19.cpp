BOOL ssl_util_path_check(ssl_pathcheck_t pcm, const char *path, apr_pool_t *p)
{
    apr_finfo_t finfo;

    if (path == NULL)
        return FALSE;
    if (pcm & SSL_PCM_EXISTS && apr_stat(&finfo, path,
                                APR_FINFO_TYPE|APR_FINFO_SIZE, p) != 0)
        return FALSE;
    if (pcm & SSL_PCM_ISREG && finfo.filetype != APR_REG)
        return FALSE;
    if (pcm & SSL_PCM_ISDIR && finfo.filetype != APR_DIR)
        return FALSE;
    if (pcm & SSL_PCM_ISNONZERO && finfo.size <= 0)
        return FALSE;
    return TRUE;
}