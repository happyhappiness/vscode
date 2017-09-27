            apr_table_unset(r->headers_in, "Content-Length");
            ap_internal_redirect_handler(req_conf->location, r);
            return OK;
            /* break; */

        case scgi_sendfile:
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00863)
                          "File subrequest to %s", req_conf->location);
            do {
                request_rec *rr;

                rr = ap_sub_req_lookup_file(req_conf->location, r,
                                            r->output_filters);
                if (rr->status == HTTP_OK && rr->finfo.filetype != APR_NOFILE) {
