            if (te && !apr_table_get(rp->headers_in, "Transfer-Encoding")) {
                apr_table_add(rp->headers_in, "Transfer-Encoding", te);
            }

            apr_table_unset(r->headers_out,"Transfer-Encoding");

            ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
                         "proxy: start body send");

            /*
             * if we are overriding the errors, we can't put the content
             * of the page into the brigade
             */
