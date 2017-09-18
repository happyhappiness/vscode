    str[i] = 0;
    return rv;
}



APR_DECLARE(int) apr_file_printf(apr_file_t *fptr, const char *format, ...)
{
    int cc;
    va_list ap;
    char *buf;
    int len;

