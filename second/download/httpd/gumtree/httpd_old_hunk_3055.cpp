            /* First, tuck away all already existing cookies */
            save_table = apr_table_make(r->pool, 2);
            apr_table_do(addit_dammit, save_table, r->headers_out,
                         "Set-Cookie", NULL);

            /* shove the headers direct into r->headers_out */
            ap_proxy_read_headers(r, rp, buffer, sizeof(buffer), origin,
                                  &pread_len);

            if (r->headers_out == NULL) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d header "
                             "returned by %s (%s)", major, minor, r->uri,
                             r->method);
                backend->close += 1;
                /*
                 * ap_send_error relies on a headers_out to be present. we
                 * are in a bad position here.. so force everything we send out
                 * to have nothing to do with the incoming packet
                 */
