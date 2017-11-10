apr_status_t apr_socket_close(apr_socket_t *thesocket)
{
    return apr_pool_cleanup_run(thesocket->pool, thesocket, socket_cleanup);
}