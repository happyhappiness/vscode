    const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
    const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Into ajp_marshal_into_msgb");

    if ((method = sc_for_req_method_by_id(r->method_number)) == UNKNOWN_METHOD) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_marshal_into_msgb - No such method %s",
               r->method);
        return AJP_EBAD_METHOD;
    }

