        return rc;
    }
    r->status = status;

    rc = ajp_msg_get_string(msg, &ptr);
    if (rc == APR_SUCCESS) {
        r->status_line =  apr_psprintf(r->pool, "%d %s", status, ptr);
#if defined(AS400) || defined(_OSD_POSIX)
        ap_xlate_proto_from_ascii(r->status_line, strlen(r->status_line));
#endif
    } else {
        r->status_line = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
           "ajp_unmarshal_response: status = %d", status);
