void ap_logs_child_init(apr_pool_t *p, server_rec *s)
{
    read_handle_t *cur = read_handles;

    while (cur) {
        apr_file_close(cur->handle);
        cur = cur->next;
    }
}