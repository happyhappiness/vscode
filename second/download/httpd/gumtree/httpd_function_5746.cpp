static apr_status_t ajp_marshal_into_msgb(ajp_msg_t *msg,
                                          request_rec *r,
                                          apr_uri_t *uri)
{
    int method;
    apr_uint32_t i, num_headers = 0;
    apr_byte_t is_ssl;
    char *remote_host;
    const char *session_route, *envvar;
    const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
    const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r, "Into ajp_marshal_into_msgb");

    if ((method = sc_for_req_method_by_id(r)) == UNKNOWN_METHOD) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00967)
               "ajp_marshal_into_msgb - No such method %s",
               r->method);
        return AJP_EBAD_METHOD;
    }

    is_ssl = (apr_byte_t) ap_proxy_conn_is_https(r->connection);

    if (r->headers_in && apr_table_elts(r->headers_in)) {
        const apr_array_header_t *t = apr_table_elts(r->headers_in);
        num_headers = t->nelts;
    }

    remote_host = (char *)ap_get_remote_host(r->connection, r->per_dir_config, REMOTE_HOST, NULL);

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
 * <Location /examples>
 *   ProxyPass ajp://remote:8009/servlets-examples
 *   SetEnv SSL_SESSION_ID CUSTOM_SSL_SESSION_ID
 * </Location>
 */
    /*
     * Only lookup SSL variables if we are currently running HTTPS.
     * Furthermore ensure that only variables get set in the AJP message
     * that are not NULL and not empty.
     */
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
     * Since the servlet spec allows to retrieve it via getRemotePort(),
     * we provide the port to the Tomcat connector as a request
     * attribute. Modern Tomcat versions know how to retrieve
     * the remote port from this attribute.
     */
    {
        const char *key = SC_A_REQ_REMOTE_PORT;
        char *val = apr_itoa(r->pool, r->useragent_addr->port);
        if (ajp_msg_append_uint8(msg, SC_A_REQ_ATTRIBUTE) ||
            ajp_msg_append_string(msg, key)   ||
            ajp_msg_append_string(msg, val)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00980)
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
                ajp_msg_append_string(msg, elts[i].key + 4)   ||
                ajp_msg_append_string(msg, elts[i].val)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00981)
                        "ajp_marshal_into_msgb: "
                        "Error appending attribute %s=%s",
                        elts[i].key, elts[i].val);
                return AJP_EOVERFLOW;
            }
        }
    }

    if (ajp_msg_append_uint8(msg, SC_A_ARE_DONE)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00982)
               "ajp_marshal_into_msgb: "
               "Error appending the message end");
        return AJP_EOVERFLOW;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r,
            "ajp_marshal_into_msgb: Done");
    return APR_SUCCESS;
}