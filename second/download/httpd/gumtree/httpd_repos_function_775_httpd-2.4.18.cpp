void ssl_util_ppclose(server_rec *s, apr_pool_t *p, apr_file_t *fp)
{
    apr_file_close(fp);
    return;
}