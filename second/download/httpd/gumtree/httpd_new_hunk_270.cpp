            /* In order for ap_set_keepalive to work properly, we can NOT
             * have any length information stored in the output headers.
             */
            apr_table_unset(r->headers_out,"Transfer-Encoding");
            apr_table_unset(r->headers_out,"Content-Length");

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: start body send");
             
            /*
             * if we are overriding the errors, we can't put the content
             * of the page into the brigade
             */
