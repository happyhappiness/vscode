        apr_table_unset(r->headers_in, "If-Match");
        apr_table_unset(r->headers_in, "If-Modified-Since");
        apr_table_unset(r->headers_in, "If-None-Match");
        apr_table_unset(r->headers_in, "If-Range");
        apr_table_unset(r->headers_in, "If-Unmodified-Since");

        ap_internal_redirect(r->uri, r);

        return APR_SUCCESS;
    }

    if (reason) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
