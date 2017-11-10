static int header_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    format_tag_hash = apr_hash_make(p);
    register_format_tag_handler("D", header_request_duration);
    register_format_tag_handler("t", header_request_time);
    register_format_tag_handler("e", header_request_env_var);
    register_format_tag_handler("s", header_request_ssl_var);
    register_format_tag_handler("l", header_request_loadavg);
    register_format_tag_handler("i", header_request_idle);
    register_format_tag_handler("b", header_request_busy);

    return OK;
}