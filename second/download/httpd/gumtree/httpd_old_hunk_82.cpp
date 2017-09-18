    charset_req_t *reqinfo;
    charset_filter_ctx_t *input_ctx, *output_ctx;
    apr_status_t rv;
    const char *mime_type;

    if (dc->debug >= DBGLVL_FLOW) {
        ap_log_rerror(APLOG_MARK,APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                      "uri: %s file: %s method: %d "
                      "imt: %s flags: %s%s%s %s->%s",
                      r->uri, r->filename, r->method_number,
                      r->content_type ? r->content_type : "(unknown)",
                      r->main     ? "S" : "",    /* S if subrequest */
                      r->prev     ? "R" : "",    /* R if redirect */
