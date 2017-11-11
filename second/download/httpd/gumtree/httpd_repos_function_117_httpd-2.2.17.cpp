static int accessible(apr_pool_t *pool, char *fname, int mode)
{
    apr_file_t *f = NULL;

    if (apr_file_open(&f, fname, mode, APR_OS_DEFAULT, pool) != APR_SUCCESS) {
        return 0;
    }
    apr_file_close(f);
    return 1;
}