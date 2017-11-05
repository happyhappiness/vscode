static apr_status_t reset_conf_vector_length(void *dummy)
{
    conf_vector_length = max_modules;
    return APR_SUCCESS;
}