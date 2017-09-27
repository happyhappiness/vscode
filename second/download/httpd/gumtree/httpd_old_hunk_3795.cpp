    apr_uint16_t  num_headers;
    int i;

    rc = ajp_msg_get_uint16(msg, &status);

    if (rc != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00983)
                "ajp_unmarshal_response: Null status");
        return rc;
    }
    r->status = status;

    rc = ajp_msg_get_string(msg, &ptr);
    if (rc == APR_SUCCESS) {
#if APR_CHARSET_EBCDIC /* copy only if we have to */
        ptr = apr_pstrdup(r->pool, ptr);
        ap_xlate_proto_from_ascii(ptr, strlen(ptr));
#endif
        r->status_line =  apr_psprintf(r->pool, "%d %s", status, ptr);
    } else {
        r->status_line = NULL;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
           "ajp_unmarshal_response: status = %d", status);

