                                  &pread_len);

            if (r->headers_out == NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01106)
                              "bad HTTP/%d.%d header returned by %s (%s)",
                              major, minor, r->uri, r->method);
                backend->close = 1;
                /*
                 * ap_send_error relies on a headers_out to be present. we
                 * are in a bad position here.. so force everything we send out
                 * to have nothing to do with the incoming packet
                 */
                r->headers_out = apr_table_make(r->pool,1);
