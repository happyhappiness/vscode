                             "Error ajp_marshal_into_msgb - "
                             "Error appending the SSL key size");
                return APR_EGENERAL;
            }
        }
    }
    /* Forward the remote port information, which was forgotten
     * from the builtin data of the AJP 13 protocol.
     * Since the servlet spec allows to retrieve it via getRemotePort(),
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
    /* Use the environment vars prefixed with AJP_
     * and pass it to the header striping that prefix.
     */
    for (i = 0; i < (apr_uint32_t)arr->nelts; i++) {
        if (!strncmp(elts[i].key, "AJP_", 4)) {
            if (ajp_msg_append_uint8(msg, SC_A_REQ_ATTRIBUTE) ||
