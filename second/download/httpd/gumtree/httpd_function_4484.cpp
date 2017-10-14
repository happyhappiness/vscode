static int scgi_request_status(int *status, request_rec *r)
{
    scgi_request_config *req_conf;

    if (   (*status == OK)
        && (req_conf = ap_get_module_config(r->request_config,
                                            &proxy_scgi_module))) {
        switch (req_conf->type) {
        case scgi_internal_redirect:
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: " PROXY_FUNCTION ": Internal redirect to %s",
                          req_conf->location);

            r->status_line = NULL;
            if (r->method_number != M_GET) {
                /* keep HEAD, which is passed around as M_GET, too */
                r->method = "GET";
                r->method_number = M_GET;
            }
            apr_table_unset(r->headers_in, "Content-Length");
            ap_internal_redirect_handler(req_conf->location, r);
            return OK;
            /* break; */

        case scgi_sendfile:
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: " PROXY_FUNCTION ": File subrequest to %s",
                          req_conf->location);
            do {
                request_rec *rr;

                rr = ap_sub_req_lookup_file(req_conf->location, r,
                                            r->output_filters);
                if (rr->status == HTTP_OK && rr->finfo.filetype != APR_NOFILE) {
                    /*
                     * We don't touch Content-Length here. It might be
                     * borked (there's plenty of room for a race condition).
                     * Either the backend sets it or it's gonna be chunked.
                     */
                    ap_run_sub_req(rr);
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Subrequest to file '%s' not possible. "
                                  "(rr->status=%d, rr->finfo.filetype=%d)",
                                  req_conf->location, rr->status,
                                  rr->finfo.filetype);
                    *status = HTTP_INTERNAL_SERVER_ERROR;
                    return *status;
                }
            } while(0);

            return OK;
            /* break; */
        }
    }

    return DECLINED;
}