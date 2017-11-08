static apr_status_t
mc_conn_destruct(void *conn_, void *params, apr_pool_t *pool)
{
    apr_memcache_conn_t *conn = (apr_memcache_conn_t*)conn_;
    struct iovec vec[2];
    apr_size_t written;
    
    /* send a quit message to the memcached server to be nice about it. */
    vec[0].iov_base = MC_QUIT;
    vec[0].iov_len = MC_QUIT_LEN;

    vec[1].iov_base = MC_EOL;
    vec[1].iov_len = MC_EOL_LEN;
    
    /* Return values not checked, since we just want to make it go away. */
    apr_socket_sendv(conn->sock, vec, 2, &written);
    apr_socket_close(conn->sock);

    apr_pool_destroy(conn->p);
    
    return APR_SUCCESS;
}