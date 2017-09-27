     * we provide the port to the Tomcat connector as a request
     * attribute. Modern Tomcat versions know how to retrieve
     * the remote port from this attribute.
     */
    {
        const char *key = SC_A_REQ_REMOTE_PORT;
        char *val = apr_itoa(r->pool, r->connection->remote_addr->port);
        if (ajp_msg_append_uint8(msg, SC_A_REQ_ATTRIBUTE) ||
            ajp_msg_append_string(msg, key)   ||
            ajp_msg_append_string(msg, val)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                    "ajp_marshal_into_msgb: "
                    "Error appending attribute %s=%s",
                    key, val);
            return AJP_EOVERFLOW;
        }
    }
