{
    ajp_msg_t *msg;
    apr_status_t rc;

    rc = ajp_msg_create(r->pool, buffsize, &msg);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00987)
               "ajp_send_header: ajp_msg_create failed");
        return rc;
    }

    rc = ajp_marshal_into_msgb(msg, r, uri);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00988)
               "ajp_send_header: ajp_marshal_into_msgb failed");
        return rc;
    }

    rc = ajp_ilink_send(sock, msg);
    ajp_msg_log(r, msg, "ajp_send_header: ajp_ilink_send packet dump");
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00989)
               "ajp_send_header: ajp_ilink_send failed");
        return rc;
    }

    return APR_SUCCESS;
}
