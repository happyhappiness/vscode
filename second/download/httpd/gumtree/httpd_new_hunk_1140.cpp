                 */
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            conn->worker->s->transferred += bufsiz;
            send_body = 1;
        }
        else if (content_length > 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                         "proxy: read zero bytes, expecting"
                         " %" APR_OFF_T_FMT " bytes",
                         content_length);
            status = ajp_send_data_msg(conn->sock, msg, 0);
            if (status != APR_SUCCESS) {
                /* We had a failure: Close connection to backend */
                conn->close++;
                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                            "proxy: send failed to %pI (%s)",
                            conn->worker->cp->addr,
                            conn->worker->hostname);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            else {
                /* Client send zero bytes with C-L > 0
                 */
                return HTTP_BAD_REQUEST;
            }
        }
    }

    /* read the response */
    conn->data = NULL;
    status = ajp_read_header(conn->sock, r, maxsize,
                             (ajp_msg_t **)&(conn->data));
