
/*
 * Build the ajp header message and send it
 */
apr_status_t ajp_send_header(apr_socket_t *sock,
                             request_rec *r,
                             apr_size_t buffsize,
                             apr_uri_t *uri)
{
    ajp_msg_t *msg;
    apr_status_t rc;

    rc = ajp_msg_create(r->pool, buffsize, &msg);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_send_header: ajp_msg_create failed");
        return rc;
    }

