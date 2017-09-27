    const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
    const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r, "Into ajp_marshal_into_msgb");

    if ((method = sc_for_req_method_by_id(r)) == UNKNOWN_METHOD) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r, APLOGNO(02437)
               "ajp_marshal_into_msgb - Sending unknown method %s as request attribute",
               r->method);
        method = SC_M_JK_STORED;
    }

    is_ssl = (apr_byte_t) ap_proxy_conn_is_https(r->connection);

    if (r->headers_in && apr_table_elts(r->headers_in)) {
        const apr_array_header_t *t = apr_table_elts(r->headers_in);
