apr_status_t apr_file_socket_pipe_create(apr_file_t **in,
                                         apr_file_t **out,
                                         apr_pool_t *p)
{
    apr_status_t rv;
    SOCKET rd;
    SOCKET wr;

    if ((rv = create_socket_pipe(&rd, &wr)) != APR_SUCCESS) {
        return rv;
    }
    (*in) = (apr_file_t *)apr_pcalloc(p, sizeof(apr_file_t));
    (*in)->pool = p;
    (*in)->fname = NULL;
    (*in)->pipe = 1;
    (*in)->timeout = -1;
    (*in)->ungetchar = -1;
    (*in)->eof_hit = 0;
    (*in)->filePtr = 0;
    (*in)->bufpos = 0;
    (*in)->dataRead = 0;
    (*in)->direction = 0;
    (*in)->pOverlapped = (OVERLAPPED*)apr_pcalloc(p, sizeof(OVERLAPPED));
    (*in)->filehand = (HANDLE)rd;

    (*out) = (apr_file_t *)apr_pcalloc(p, sizeof(apr_file_t));
    (*out)->pool = p;
    (*out)->fname = NULL;
    (*out)->pipe = 1;
    (*out)->timeout = -1;
    (*out)->ungetchar = -1;
    (*out)->eof_hit = 0;
    (*out)->filePtr = 0;
    (*out)->bufpos = 0;
    (*out)->dataRead = 0;
    (*out)->direction = 0;
    (*out)->pOverlapped = (OVERLAPPED*)apr_pcalloc(p, sizeof(OVERLAPPED));
    (*out)->filehand = (HANDLE)wr;

    apr_pool_cleanup_register(p, (void *)(*in), socket_pipe_cleanup,
                              apr_pool_cleanup_null);
    apr_pool_cleanup_register(p, (void *)(*out), socket_pipe_cleanup,
                              apr_pool_cleanup_null);

    return rv;
}