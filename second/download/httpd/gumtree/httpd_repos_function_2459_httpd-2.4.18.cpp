static apr_status_t session_pool_cleanup(void *data)
{
    h2_session *session = data;
    
    /* keep us from destroying the pool, since that is already ongoing. */
    session->pool = NULL;
    h2_session_destroy(session);
    return APR_SUCCESS;
}