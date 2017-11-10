apr_status_t ajp_handle_cping_cpong(apr_socket_t *sock,
                                    request_rec *r,
                                    apr_interval_time_t timeout)
{
    ajp_msg_t *msg;
    apr_status_t rc, rv;
    apr_interval_time_t org;
    apr_byte_t result;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r,
                         "Into ajp_handle_cping_cpong");

    rc = ajp_msg_create(r->pool, AJP_PING_PONG_SZ, &msg);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01007)
               "ajp_handle_cping_cpong: ajp_msg_create failed");
        return rc;
    }

    rc = ajp_msg_serialize_cping(msg);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01008)
               "ajp_handle_cping_cpong: ajp_marshal_into_msgb failed");
        return rc;
    }

    rc = ajp_ilink_send(sock, msg);
    ajp_msg_log(r, msg, "ajp_handle_cping_cpong: ajp_ilink_send packet dump");
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01009)
               "ajp_handle_cping_cpong: ajp_ilink_send failed");
        return rc;
    }

    rc = apr_socket_timeout_get(sock, &org);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01010)
               "ajp_handle_cping_cpong: apr_socket_timeout_get failed");
        return rc;
    }

    /* Set CPING/CPONG response timeout */
    rc = apr_socket_timeout_set(sock, timeout);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01011)
               "ajp_handle_cping_cpong: apr_socket_timeout_set failed");
        return rc;
    }
    ajp_msg_reuse(msg);

    /* Read CPONG reply */
    rv = ajp_ilink_receive(sock, msg);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01012)
               "ajp_handle_cping_cpong: ajp_ilink_receive failed");
        goto cleanup;
    }

    ajp_msg_log(r, msg, "ajp_handle_cping_cpong: ajp_ilink_receive packet dump");
    rv = ajp_msg_get_uint8(msg, &result);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01013)
               "ajp_handle_cping_cpong: invalid CPONG message");
        goto cleanup;
    }
    if (result != CMD_AJP13_CPONG) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01014)
               "ajp_handle_cping_cpong: awaited CPONG, received %d ",
               result);
        rv = APR_EGENERAL;
        goto cleanup;
    }

cleanup:
    /* Restore original socket timeout */
    rc = apr_socket_timeout_set(sock, org);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01015)
               "ajp_handle_cping_cpong: apr_socket_timeout_set failed");
        return rc;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r,
                         "ajp_handle_cping_cpong: Done");
    return rv;
}