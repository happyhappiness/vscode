static void *create_isapi_dir_config(apr_pool_t *p, char *dummy)
{
    isapi_dir_conf *dir = apr_palloc(p, sizeof(isapi_dir_conf));

    dir->read_ahead_buflen = ISAPI_UNDEF;
    dir->log_unsupported   = ISAPI_UNDEF;
    dir->log_to_errlog     = ISAPI_UNDEF;
    dir->log_to_query      = ISAPI_UNDEF;
    dir->fake_async        = ISAPI_UNDEF;

    return dir;
}