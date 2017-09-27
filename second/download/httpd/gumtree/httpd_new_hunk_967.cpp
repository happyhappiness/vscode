    }
    return APR_SUCCESS; 
}

APR_DECLARE(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile)
{
    apr_size_t len = strlen(str);

    return apr_file_write(thefile, str, &len);
}

APR_DECLARE(apr_status_t) apr_file_gets(char *str, int len, apr_file_t *thefile)
{
