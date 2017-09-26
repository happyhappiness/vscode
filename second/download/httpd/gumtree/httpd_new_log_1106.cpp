E(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile)
{
    return apr_file_write_full(thefile, str, strlen(str), NULL);
};