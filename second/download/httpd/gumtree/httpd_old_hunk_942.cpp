            (r->status != HTTP_NO_CONTENT) &&      /* not 204 */
            (r->status != HTTP_RESET_CONTENT) &&   /* not 205 */
            (r->status != HTTP_NOT_MODIFIED)) {    /* not 304 */

            /* We need to copy the output headers and treat them as input
             * headers as well.  BUT, we need to do this before we remove
             * TE and C-L, so that they are preserved accordingly for
             * ap_http_filter to know where to end.
             */
            rp->headers_in = apr_table_copy(r->pool, r->headers_out);

            /* In order for ap_set_keepalive to work properly, we can NOT
             * have any length information stored in the output headers.
             */
            apr_table_unset(r->headers_out,"Transfer-Encoding");
            apr_table_unset(r->headers_out,"Content-Length");

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: start body send");
             
            /*
             * if we are overriding the errors, we can't put the content
