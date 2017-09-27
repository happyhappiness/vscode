    r->read_body = read_policy;
    r->read_chunked = 0;
    r->remaining = 0;

    if (tenc) {
        if (strcasecmp(tenc, "chunked")) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01592)
                          "Unknown Transfer-Encoding %s", tenc);
            return HTTP_NOT_IMPLEMENTED;
        }
        if (r->read_body == REQUEST_CHUNKED_ERROR) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01593)
                          "chunked Transfer-Encoding forbidden: %s", r->uri);
            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        char *endstr;

        if (apr_strtoff(&r->remaining, lenp, &endstr, 10)
            || *endstr || r->remaining < 0) {
            r->remaining = 0;
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01594)
                          "Invalid Content-Length");
            return HTTP_BAD_REQUEST;
        }
    }

    if ((r->read_body == REQUEST_NO_BODY)
        && (r->read_chunked || (r->remaining > 0))) {
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01595)
                      "%s with body is not allowed for %s", r->method, r->uri);
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }

#ifdef AP_DEBUG
    {
        /* Make sure ap_getline() didn't leave any droppings. */
        core_request_config *req_cfg =
            (core_request_config *)ap_get_core_module_config(r->request_config);
        AP_DEBUG_ASSERT(APR_BRIGADE_EMPTY(req_cfg->bb));
    }
#endif

    return OK;
}
