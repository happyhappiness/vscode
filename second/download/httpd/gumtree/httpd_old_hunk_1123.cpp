            break;
        }
        result = ajp_parse_type(r, conn->data);
    }
    apr_brigade_destroy(input_brigade);

    apr_brigade_destroy(output_brigade);

    if (status != APR_SUCCESS) {
        /* We had a failure: Close connection to backend */
        conn->close++;
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: send body failed to %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        return HTTP_SERVICE_UNAVAILABLE;
    }

    /* Nice we have answer to send to the client */
    if (result == CMD_AJP13_END_RESPONSE && isok) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: got response from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
