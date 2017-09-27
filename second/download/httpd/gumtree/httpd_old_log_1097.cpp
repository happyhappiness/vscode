D(int) apr_file_printf(apr_file_t *fptr, 
                                        const char *format, ...)
{
    apr_status_t cc;
    va_list ap;
    char *buf;
    int len;

    buf = malloc(HUGE_STRING_LEN);
    if (buf == NULL) {
        return 0;
    }
    va_start(ap, format);