static void *merge_isapi_dir_configs(apr_pool_t *p, void *base_, void *add_)
{
    isapi_dir_conf *base = (isapi_dir_conf *) base_;
    isapi_dir_conf *add = (isapi_dir_conf *) add_;
    isapi_dir_conf *dir = apr_palloc(p, sizeof(isapi_dir_conf));

    dir->read_ahead_buflen = (add->read_ahead_buflen == ISAPI_UNDEF)
                                ? base->read_ahead_buflen
                                 : add->read_ahead_buflen;
    dir->log_unsupported   = (add->log_unsupported == ISAPI_UNDEF)
                                ? base->log_unsupported
                                 : add->log_unsupported;
    dir->log_to_errlog     = (add->log_to_errlog == ISAPI_UNDEF)
                                ? base->log_to_errlog
                                 : add->log_to_errlog;
    dir->log_to_query      = (add->log_to_query == ISAPI_UNDEF)
                                ? base->log_to_query
                                 : add->log_to_query;
    dir->fake_async        = (add->fake_async == ISAPI_UNDEF)
                                ? base->fake_async
                                 : add->fake_async;

    return dir;
}