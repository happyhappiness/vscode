static void *create_includes_server_config(apr_pool_t *p, server_rec *server)
{
    include_server_config *result;

    result = apr_palloc(p, sizeof(include_server_config));
    result->default_end_tag    = DEFAULT_END_SEQUENCE;
    result->default_start_tag  = DEFAULT_START_SEQUENCE;

    return result;
}