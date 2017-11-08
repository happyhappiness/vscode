static apr_status_t conn_connect(apr_memcache_conn_t *conn)
{
    apr_status_t rv = APR_SUCCESS;
    apr_sockaddr_t *sa;
#if APR_HAVE_SOCKADDR_UN
    apr_int32_t family = conn->ms->host[0] != '/' ? APR_INET : APR_UNIX;
#else
    apr_int32_t family = APR_INET;
#endif

    rv = apr_sockaddr_info_get(&sa, conn->ms->host, family, conn->ms->port, 0, conn->p);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_socket_timeout_set(conn->sock, 1 * APR_USEC_PER_SEC);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_socket_connect(conn->sock, sa);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_socket_timeout_set(conn->sock, -1);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    return rv;
}