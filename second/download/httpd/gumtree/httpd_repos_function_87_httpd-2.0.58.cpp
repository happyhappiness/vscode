static int get_line(char *s, int n, apr_file_t *f)
{
    register int i = 0;
    char ch;
    apr_status_t rv = APR_EINVAL;

    while (i < (n - 1) && 
           ((rv = apr_file_getc(&ch, f)) == APR_SUCCESS) && (ch != '\n')) {
        s[i++] = ch;
    }
    if (ch == '\n')
        s[i++] = ch;
    s[i] = '\0';

    if (rv != APR_SUCCESS) 
        return 1;

    return 0;
}