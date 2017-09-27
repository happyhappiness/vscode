                              "ajp_marshal_into_msgb: "
                              "Error appending the SSL key size");
                return APR_EGENERAL;
            }
        }
    }
    /* If the method was unrecognized, encode it as an attribute */
    if (method == SC_M_JK_STORED) {
        if (ajp_msg_append_uint8(msg, SC_A_STORED_METHOD)
            || ajp_msg_append_string(msg, r->method)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02438)
                          "ajp_marshal_into_msgb: "
                          "Error appending the method '%s' as request attribute",
                          r->method);
            return AJP_EOVERFLOW;
        }
    }
    /* Forward the remote port information, which was forgotten
     * from the builtin data of the AJP 13 protocol.
     * Since the servlet spec allows to retrieve it via getRemotePort(),
     * we provide the port to the Tomcat connector as a request
     * attribute. Modern Tomcat versions know how to retrieve
     * the remote port from this attribute.
