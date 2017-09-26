                conn->close++;
                apr_brigade_destroy(input_brigade);
                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                             "proxy: send failed to %pI (%s)",
                             conn->worker->cp->addr,
                             conn->worker->hostname);
                /*
                 * It is fatal when we failed to send a (part) of the request
                 * body.
                 */
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            conn->worker->s->transferred += bufsiz;
            send_body = 1;
        }
    }

    /* read the response */
    conn->data = NULL;
    status = ajp_read_header(conn->sock, r, maxsize,
