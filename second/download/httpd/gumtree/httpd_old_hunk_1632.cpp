            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_read_header: ajp_msg_reuse failed");
            return rc;
        }
    }
    else {
        rc = ajp_msg_create(r->pool, msg);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_read_header: ajp_msg_create failed");
            return rc;
        }
    }
