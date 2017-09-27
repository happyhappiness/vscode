    }

    /* Always return the SUCCESS */
    return APR_SUCCESS;
}

/* DEPRECATED */
PROXY_DECLARE(apr_status_t) ap_proxy_ssl_connection_cleanup(proxy_conn_rec *conn,
                                                            request_rec *r)
{
    apr_status_t rv;

    /*
     * If we have an existing SSL connection it might be possible that the
     * server sent some SSL message we have not read so far (e.g. an SSL
     * shutdown message if the server closed the keepalive connection while
     * the connection was held unused in our pool).
     * So ensure that if present (=> APR_NONBLOCK_READ) it is read and
     * processed. We don't expect any data to be in the returned brigade.
     */
    if (conn->sock && conn->connection) {
        rv = ap_get_brigade(conn->connection->input_filters, conn->tmp_bb,
                            AP_MODE_READBYTES, APR_NONBLOCK_READ,
                            HUGE_STRING_LEN);
        if (!APR_BRIGADE_EMPTY(conn->tmp_bb)) {
            apr_off_t len;

            rv = apr_brigade_length(conn->tmp_bb, 0, &len);
            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, rv, r,
                          "SSL cleanup brigade contained %"
                          APR_OFF_T_FMT " bytes of data.", len);
            apr_brigade_cleanup(conn->tmp_bb);
        }
        if ((rv != APR_SUCCESS) && !APR_STATUS_IS_EAGAIN(rv)) {
            socket_cleanup(conn);
        }
    }
    return APR_SUCCESS;
}

/* reslist constructor */
static apr_status_t connection_constructor(void **resource, void *params,
