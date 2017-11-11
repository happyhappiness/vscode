static APR_INLINE void do_double_reverse (conn_rec *conn)
{
    apr_sockaddr_t *sa;
    apr_status_t rv;

    if (conn->double_reverse) {
        /* already done */
        return;
    }

    if (conn->remote_host == NULL || conn->remote_host[0] == '\0') {
        /* single reverse failed, so don't bother */
        conn->double_reverse = -1;
        return;
    }

    rv = apr_sockaddr_info_get(&sa, conn->remote_host, APR_UNSPEC, 0, 0, conn->pool);
    if (rv == APR_SUCCESS) {
        while (sa) {
            if (apr_sockaddr_equal(sa, conn->remote_addr)) {
                conn->double_reverse = 1;
                return;
            }

            sa = sa->next;
        }
    }

    conn->double_reverse = -1;
}