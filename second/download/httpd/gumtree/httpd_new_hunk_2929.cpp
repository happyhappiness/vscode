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
