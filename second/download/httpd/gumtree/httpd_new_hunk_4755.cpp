             * Now the connection is in the wrong state on the backend.
             * Sending an empty data msg doesn't help either as it does
             * not move this connection to the correct state on the backend
             * for later resusage by the next request again.
             * Close it to clean things up.
             */
            conn->close = 1;
            return HTTP_BAD_REQUEST;
        }
    }

    /* read the response */
    conn->data = NULL;
    status = ajp_read_header(conn->sock, r, maxsize,
                             (ajp_msg_t **)&(conn->data));
    if (status != APR_SUCCESS) {
        /* We had a failure: Close connection to backend */
        conn->close = 1;
        apr_brigade_destroy(input_brigade);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00878)
                      "read response failed from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);

