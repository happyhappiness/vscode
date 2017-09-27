    ajp_msg_reset(msg);

    if (ajp_msg_append_uint8(msg, CMD_AJP13_FORWARD_REQUEST)     ||
        ajp_msg_append_uint8(msg, (apr_byte_t) method)           ||
        ajp_msg_append_string(msg, r->protocol)                  ||
        ajp_msg_append_string(msg, uri->path)                    ||
        ajp_msg_append_string(msg, r->useragent_ip)              ||
        ajp_msg_append_string(msg, remote_host)                  ||
        ajp_msg_append_string(msg, ap_get_server_name(r))        ||
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
        const apr_table_entry_t *elts = (apr_table_entry_t *)t->elts;

        if ((sc = sc_for_req_header(elts[i].key)) != UNKNOWN_METHOD) {
            if (ajp_msg_append_uint16(msg, (apr_uint16_t)sc)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00969)
                       "ajp_marshal_into_msgb: "
                       "Error appending the header name");
                return AJP_EOVERFLOW;
            }
        }
        else {
            if (ajp_msg_append_string(msg, elts[i].key)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00970)
                       "ajp_marshal_into_msgb: "
                       "Error appending the header name");
                return AJP_EOVERFLOW;
            }
        }

        if (ajp_msg_append_string(msg, elts[i].val)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00971)
                   "ajp_marshal_into_msgb: "
                   "Error appending the header value");
            return AJP_EOVERFLOW;
        }
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                   "ajp_marshal_into_msgb: Header[%d] [%s] = [%s]",
                   i, elts[i].key, elts[i].val);
    }

/* XXXX need to figure out how to do this
    if (s->secret) {
        if (ajp_msg_append_uint8(msg, SC_A_SECRET) ||
            ajp_msg_append_string(msg, s->secret)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                   "Error ajp_marshal_into_msgb - "
                   "Error appending secret");
            return APR_EGENERAL;
        }
    }
 */

    if (r->user) {
        if (ajp_msg_append_uint8(msg, SC_A_REMOTE_USER) ||
            ajp_msg_append_string(msg, r->user)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00972)
                   "ajp_marshal_into_msgb: "
                   "Error appending the remote user");
            return AJP_EOVERFLOW;
        }
    }
    if (r->ap_auth_type) {
        if (ajp_msg_append_uint8(msg, SC_A_AUTH_TYPE) ||
            ajp_msg_append_string(msg, r->ap_auth_type)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00973)
                   "ajp_marshal_into_msgb: "
                   "Error appending the auth type");
            return AJP_EOVERFLOW;
        }
    }
    /* XXXX  ebcdic (args converted?) */
    if (uri->query) {
        if (ajp_msg_append_uint8(msg, SC_A_QUERY_STRING) ||
            ajp_msg_append_string(msg, uri->query)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00974)
                   "ajp_marshal_into_msgb: "
                   "Error appending the query string");
            return AJP_EOVERFLOW;
        }
    }
    if ((session_route = apr_table_get(r->notes, "session-route"))) {
        if (ajp_msg_append_uint8(msg, SC_A_JVM_ROUTE) ||
            ajp_msg_append_string(msg, session_route)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00975)
                   "ajp_marshal_into_msgb: "
                   "Error appending the jvm route");
            return AJP_EOVERFLOW;
        }
    }
/* XXX: Is the subprocess_env a right place?
