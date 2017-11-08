static apr_status_t clear_handle_list(void *v)
{
    read_handles = NULL;
    return APR_SUCCESS;
}