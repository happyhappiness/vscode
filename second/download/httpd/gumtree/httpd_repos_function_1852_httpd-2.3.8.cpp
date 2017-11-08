static int handle_headers(request_rec *r,
                          int *state,
                          char *readbuf,
                          apr_bucket_brigade *ob)
{
    conn_rec *c = r->connection;
    const char *itr = readbuf;

    while (*itr) {
        if (*itr == '\r') {
            switch (*state) {
                case HDR_STATE_GOT_CRLF:
                    *state = HDR_STATE_GOT_CRLFCR;
                    break;

                default:
                    *state = HDR_STATE_GOT_CR;
                    break;
            }
        }
        else if (*itr == '\n') {
            switch (*state) {
                 case HDR_STATE_GOT_LF:
                     *state = HDR_STATE_DONE_WITH_HEADERS;
                     break;

                 case HDR_STATE_GOT_CR:
                     *state = HDR_STATE_GOT_CRLF;
                     break;

                 case HDR_STATE_GOT_CRLFCR:
                     *state = HDR_STATE_DONE_WITH_HEADERS;
                     break;

                 default:
                     *state = HDR_STATE_GOT_LF;
                     break;
            }
        }
        else {
            *state = HDR_STATE_READING_HEADERS;
        }

        if (*state == HDR_STATE_DONE_WITH_HEADERS)
            break;

        ++itr;
    }

    if (*state == HDR_STATE_DONE_WITH_HEADERS) {
        int status = ap_scan_script_header_err_brigade(r, ob, NULL);
        if (status != OK) {
            apr_bucket *b;

            r->status = status;

            apr_brigade_cleanup(ob);

            b = apr_bucket_eos_create(c->bucket_alloc);

            APR_BRIGADE_INSERT_TAIL(ob, b);

            ap_pass_brigade(r->output_filters, ob);

            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: FCGI: Error parsing script headers");

            return -1;
        }
        else {
            return 1;
        }
    }

    return 0;
}