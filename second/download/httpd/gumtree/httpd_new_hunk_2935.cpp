#endif
        r->status_line =  apr_psprintf(r->pool, "%d %s", status, ptr);
    } else {
        r->status_line = NULL;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
           "ajp_unmarshal_response: status = %d", status);

    rc = ajp_msg_get_uint16(msg, &num_headers);
    if (rc == APR_SUCCESS) {
        apr_table_t *save_table;

