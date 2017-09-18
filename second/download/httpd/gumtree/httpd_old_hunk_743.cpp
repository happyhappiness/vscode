     * get away with storing it if we hit an error first. 
     */
    *str = '\0'; 
    return rv;
}

APR_DECLARE(int) apr_file_printf(apr_file_t *fptr, const char *format, ...)
{
    apr_status_t cc;
    va_list ap;
    char *buf;
    int len;

