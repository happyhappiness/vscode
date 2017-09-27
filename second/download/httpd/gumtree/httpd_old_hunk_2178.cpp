                conn->close++;
                apr_brigade_destroy(input_brigade);
                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                             "proxy: send failed to %pI (%s)",
                             conn->worker->cp->addr,
                             conn->worker->hostname);
                return HTTP_SERVICE_UNAVAILABLE;
            }
            conn->worker->s->transferred += bufsiz;
        }
    }

    /* read the response */
    conn->data = NULL;
    status = ajp_read_header(conn->sock, r, maxsize,
