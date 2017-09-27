    }
    if (session->pool) {
        apr_pool_destroy(session->pool);
    }
}

static apr_status_t h2_session_shutdown(h2_session *session, int error, 
                                        const char *msg, int force_close)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(session);
    if (!msg && error) {
        msg = nghttp2_strerror(error);
    }
    
    if (error || force_close) {
        /* not a graceful shutdown, we want to leave... 
