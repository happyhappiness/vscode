     */

    /* send request headers */
    status = ajp_send_header(conn->sock, r, maxsize, uri);
    if (status != APR_SUCCESS) {
        conn->close++;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00868)
                      "request failed to %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
        if (status == AJP_EOVERFLOW)
            return HTTP_BAD_REQUEST;
        else if  (status == AJP_EBAD_METHOD) {
            return HTTP_NOT_IMPLEMENTED;
        } else {
            /*
             * This is only non fatal when the method is idempotent. In this
             * case we can dare to retry it with a different worker if we are
             * a balancer member.
             */
            if (is_idempotent(r) == METHOD_IDEMPOTENT) {
