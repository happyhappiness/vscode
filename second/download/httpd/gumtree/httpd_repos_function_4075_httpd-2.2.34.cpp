static const char *make_shm_open_safe_name(const char *filename,
                                           apr_pool_t *pool)
{
    apr_ssize_t flen;
    unsigned int h1, h2;

    if (filename == NULL) {
        return NULL;
    }

    flen = strlen(filename);
    h1 = (apr_hashfunc_default(filename, &flen) & 0xffffffff);
    h2 = (rshash(filename) & 0xffffffff);
    return apr_psprintf(pool, "/ShM.%xH%x", h1, h2);

}