static int test_tempdir(const char *temp_dir, apr_pool_t *p)
{
    apr_file_t *dummy_file;
    const char *path = apr_pstrcat(p, temp_dir, "/apr-tmp.XXXXXX", NULL);

    if (apr_file_mktemp(&dummy_file, (char *)path, 0, p) == APR_SUCCESS) {
        if (apr_file_putc('!', dummy_file) == APR_SUCCESS) {
            if (apr_file_close(dummy_file) == APR_SUCCESS) {
                return 1;
            }
        }
    }
    return 0;
}