apr_status_t ajp_read_header(apr_socket_t *sock,
                             request_rec  *r,
                             apr_size_t buffsize,
                             ajp_msg_t **msg)
{
    apr_byte_t result;
    apr_status_t rc;

    if (*msg) {
        rc = ajp_msg_reuse(*msg);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_read_header: ajp_msg_reuse failed");
            return rc;
        }
    }
    else {
        rc = ajp_msg_create(r->pool, buffsize, msg);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_read_header: ajp_msg_create failed");
            return rc;
        }
    }
    ajp_msg_reset(*msg);
    rc = ajp_ilink_receive(sock, *msg);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_read_header: ajp_ilink_receive failed");
        return rc;
    }
    rc = ajp_msg_peek_uint8(*msg, &result);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_read_header: ajp_ilink_received %02x", result);
    return APR_SUCCESS;
}