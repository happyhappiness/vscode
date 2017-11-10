static apr_status_t cfg_getstr(void *buf, apr_size_t bufsiz, void *param)
{
    return apr_file_gets(buf, bufsiz, param);
}