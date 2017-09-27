    session->unsent_promises = 0;
    session->unsent_submits = 0;
    
    return APR_SUCCESS;
}

static apr_status_t h2_session_receive(void *ctx, const char *data, 
                                       apr_size_t len, apr_size_t *readlen)
{
    h2_session *session = ctx;
    ssize_t n;
    
