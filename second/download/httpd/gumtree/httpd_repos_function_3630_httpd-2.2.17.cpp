apr_status_t apr_file_socket_pipe_close(apr_file_t *file)
{
    apr_status_t stat;
    if (!file->pipe)
        return apr_file_close(file);
    if ((stat = socket_pipe_cleanup(file)) == APR_SUCCESS) {
        apr_pool_cleanup_kill(file->pool, file, socket_pipe_cleanup);

        if (file->mutex) {
            apr_thread_mutex_destroy(file->mutex);
        }

        return APR_SUCCESS;
    }
    return stat;
}