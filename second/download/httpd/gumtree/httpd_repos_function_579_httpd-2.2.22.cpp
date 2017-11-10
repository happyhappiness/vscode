static int header_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    format_tag_hash = apr_hash_make(p);
    register_format_tag_handler("D", (const void *)header_request_duration);
    register_format_tag_handler("t", (const void *)header_request_time);
    register_format_tag_handler("e", (const void *)header_request_env_var);
    register_format_tag_handler("s", (const void *)header_request_ssl_var);

    return OK;
}