    /* I would love to print this stuff out to the file, but I will
     * get that working later.  :)  For now, just return.
     */
    return -1;
}

APR_DECLARE(int) apr_file_printf(apr_file_t *fptr, const char *format, ...)
{
    int cc;
    va_list ap;
    char *buf;
    int len;

