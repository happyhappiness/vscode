E(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile)
{
    apr_size_t nbytes = strlen(str);

    return apr_file_write(thefile, str, &nbytes);
};