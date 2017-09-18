                return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                apr_pstrcat(p, "Corrupt status line returned by remote "
                            "server: ", buffer, NULL));
            }
            backasswards = 0;

            keepchar = buffer[12];
            if (keepchar == '\0') {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d status line "
                             "returned by %s (%s)", major, minor, r->uri,
                             r->method);
            }
            buffer[12] = '\0';
            r->status = atoi(&buffer[9]);

            buffer[12] = keepchar;
            r->status_line = apr_pstrdup(p, &buffer[9]);
            

            /* read the headers. */
            /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
            /* Also, take care with headers with multiple occurences. */

            r->headers_out = ap_proxy_read_headers(r, rp, buffer,
