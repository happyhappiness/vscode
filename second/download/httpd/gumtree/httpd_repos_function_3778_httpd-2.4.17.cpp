static int getsfunc_FILE(char *buf, int len, void *f)
{
    return apr_file_gets(buf, len, (apr_file_t *) f) == APR_SUCCESS;
}