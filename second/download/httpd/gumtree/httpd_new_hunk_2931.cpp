    if (is_ssl) {
        if ((envvar = ap_proxy_ssl_val(r->pool, r->server, r->connection, r,
                                       AJP13_SSL_CLIENT_CERT_INDICATOR))
            && envvar[0]) {
            if (ajp_msg_append_uint8(msg, SC_A_SSL_CERT)
                || ajp_msg_append_string(msg, envvar)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00976)
                              "ajp_marshal_into_msgb: "
                              "Error appending the SSL certificates");
                return AJP_EOVERFLOW;
            }
        }

        if ((envvar = ap_proxy_ssl_val(r->pool, r->server, r->connection, r,
                                       AJP13_SSL_CIPHER_INDICATOR))
            && envvar[0]) {
            if (ajp_msg_append_uint8(msg, SC_A_SSL_CIPHER)
                || ajp_msg_append_string(msg, envvar)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00977)
                              "ajp_marshal_into_msgb: "
                              "Error appending the SSL ciphers");
                return AJP_EOVERFLOW;
            }
        }

        if ((envvar = ap_proxy_ssl_val(r->pool, r->server, r->connection, r,
                                       AJP13_SSL_SESSION_INDICATOR))
            && envvar[0]) {
            if (ajp_msg_append_uint8(msg, SC_A_SSL_SESSION)
                || ajp_msg_append_string(msg, envvar)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00978)
                              "ajp_marshal_into_msgb: "
                              "Error appending the SSL session");
                return AJP_EOVERFLOW;
            }
        }

        /* ssl_key_size is required by Servlet 2.3 API */
        if ((envvar = ap_proxy_ssl_val(r->pool, r->server, r->connection, r,
                                       AJP13_SSL_KEY_SIZE_INDICATOR))
            && envvar[0]) {

            if (ajp_msg_append_uint8(msg, SC_A_SSL_KEY_SIZE)
                || ajp_msg_append_uint16(msg, (unsigned short) atoi(envvar))) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00979)
                              "ajp_marshal_into_msgb: "
                              "Error appending the SSL key size");
                return APR_EGENERAL;
            }
        }
    }
    /* Forward the remote port information, which was forgotten
     * from the builtin data of the AJP 13 protocol.
