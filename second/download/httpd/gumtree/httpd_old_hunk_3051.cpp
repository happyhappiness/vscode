                    /* if we've already started loading headers_out, then
                     * return what we've accumulated so far, in the hopes
                     * that they are useful; also note that we likely pre-read
                     * the first line of the response.
                     */
                    if (saw_headers) {
                        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                         "proxy: Starting body due to bogus non-header in headers "
                         "returned by %s (%s)", r->uri, r->method);
                        *pread_len = len;
                        return ;
                    } else {
                         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                         "proxy: No HTTP headers "
                         "returned by %s (%s)", r->uri, r->method);
                        return ;
                    }
                }
            }
            /* this is the psc->badopt == bad_ignore case */
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                         "proxy: Ignoring bogus HTTP header "
                         "returned by %s (%s)", r->uri, r->method);
            continue;
        }

        *value = '\0';
        ++value;
        /* XXX: RFC2068 defines only SP and HT as whitespace, this test is
