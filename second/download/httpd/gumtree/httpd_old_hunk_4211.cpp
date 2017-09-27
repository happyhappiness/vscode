        ajp_msg_append_uint16(msg, (apr_uint16_t)r->connection->local_addr->port) ||
        ajp_msg_append_uint8(msg, is_ssl)                        ||
        ajp_msg_append_uint16(msg, (apr_uint16_t) num_headers)) {

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00968)
               "ajp_marshal_into_msgb: "
               "Error appending the message begining");
        return APR_EGENERAL;
    }

    for (i = 0 ; i < num_headers ; i++) {
        int sc;
        const apr_array_header_t *t = apr_table_elts(r->headers_in);
