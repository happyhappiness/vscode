            if (rc != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "ajp_unmarshal_response: "
                       "Null header name");
                return rc;
            }
#if defined(AS400) || defined(_OSD_POSIX)
            ap_xlate_proto_from_ascii(stringname, strlen(stringname));
#endif
        }

        rc = ajp_msg_get_string(msg, &value);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_unmarshal_response: "
