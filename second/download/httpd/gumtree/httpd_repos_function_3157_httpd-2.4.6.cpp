static void close_handle_in_child(apr_pool_t *p, apr_file_t *f)
{
#ifndef WIN32
    read_handle_t *new_handle;

    new_handle = apr_pcalloc(p, sizeof(read_handle_t));
    new_handle->next = read_handles;
    new_handle->handle = f;
    read_handles = new_handle;
#endif
}