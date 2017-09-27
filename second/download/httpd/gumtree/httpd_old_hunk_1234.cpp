                 * To help mitigate HTTP Splitting, unset Content-Length
                 * and shut down the backend server connection
                 * XXX: We aught to treat such a response as uncachable
                 */
                apr_table_unset(r->headers_out, "Content-Length");
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: server %s returned Transfer-Encoding"
                             " and Content-Length", backend->hostname);
                backend->close += 1;
            }

            /*
             * Save a possible Transfer-Encoding header as we need it later for
             * ap_http_filter to know where to end.
