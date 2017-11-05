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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00990)
                   "ajp_read_header: ajp_msg_reuse failed");
            return rc;
        }
    }
    else {
        rc = ajp_msg_create(r->pool, buffsize, msg);
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00991)
                   "ajp_read_header: ajp_msg_create failed");
            return rc;
        }
    }
    ajp_msg_reset(*msg);
    rc = ajp_ilink_receive(sock, *msg);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00992)
               "ajp_read_header: ajp_ilink_receive failed");
        return rc;
    }
    ajp_msg_log(r, *msg, "ajp_read_header: ajp_ilink_receive packet dump");
    rc = ajp_msg_peek_uint8(*msg, &result);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00993)
                      "ajp_read_header: ajp_msg_peek_uint8 failed");
        return rc;
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
               "ajp_read_header: ajp_ilink_received %s (0x%02x)",
               ajp_type_str(result), result);
    return APR_SUCCESS;
}