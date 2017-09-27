     * have to block during a read.
     */

    do {
        apr_status_t rv;

        /* insure ap_rgetline allocates memory each time thru the loop
         * if there are empty lines
         */
        r->the_request = NULL;
        rv = ap_rgetline(&(r->the_request), (apr_size_t)(r->server->limit_req_line + 2),
                         &len, r, 0, bb);

        if (rv != APR_SUCCESS) {
            r->request_time = apr_time_now();

            /* ap_rgetline returns APR_ENOSPC if it fills up the
             * buffer before finding the end-of-line.  This is only going to
             * happen if it exceeds the configured limit for a request-line.
             */
            if (rv == APR_ENOSPC) {
                r->status    = HTTP_REQUEST_URI_TOO_LARGE;
                r->proto_num = HTTP_VERSION(1,0);
                r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
            }
            else if (rv == APR_TIMEUP) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else if (rv == APR_EINVAL) {
                r->status = HTTP_BAD_REQUEST;
            }
            return 0;
        }
    } while ((len <= 0) && (++num_blank_lines < max_blank_lines));

    if (APLOGrtrace5(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                      "Request received from client: %s",
                      ap_escape_logitem(r->pool, r->the_request));
    }

    /* we've probably got something to do, ignore graceful restart requests */

    r->request_time = apr_time_now();
    ll = r->the_request;
    r->method = ap_getword_white(r->pool, &ll);

#if 0
/* XXX If we want to keep track of the Method, the protocol module should do
 * it.  That support isn't in the scoreboard yet.  Hopefully next week
 * sometime.   rbb */
    ap_update_connection_status(AP_CHILD_THREAD_FROM_ID(conn->id), "Method",
                                r->method);
#endif

    uri = ap_getword_white(r->pool, &ll);

    /* Provide quick information about the request method as soon as known */

    r->method_number = ap_method_number_of(r->method);
    if (r->method_number == M_GET && r->method[0] == 'H') {
        r->header_only = 1;
    }

    ap_parse_uri(r, uri);

    if (ll[0]) {
        r->assbackwards = 0;
        pro = ll;
        len = strlen(ll);
    } else {
        r->assbackwards = 1;
        pro = "HTTP/0.9";
        len = 8;
    }
    r->protocol = apr_pstrmemdup(r->pool, pro, len);

    /* XXX ap_update_connection_status(conn->id, "Protocol", r->protocol); */

    /* Avoid sscanf in the common case */
    if (len == 8
        && pro[0] == 'H' && pro[1] == 'T' && pro[2] == 'T' && pro[3] == 'P'
        && pro[4] == '/' && apr_isdigit(pro[5]) && pro[6] == '.'
        && apr_isdigit(pro[7])) {
        r->proto_num = HTTP_VERSION(pro[5] - '0', pro[7] - '0');
    }
    else if (3 == sscanf(r->protocol, "%4s/%u.%u", http, &major, &minor)
             && (strcasecmp("http", http) == 0)
             && (minor < HTTP_VERSION(1, 0)) ) /* don't allow HTTP/0.1000 */
        r->proto_num = HTTP_VERSION(major, minor);
    else
        r->proto_num = HTTP_VERSION(1, 0);

    return 1;
}

AP_DECLARE(void) ap_get_mime_headers_core(request_rec *r, apr_bucket_brigade *bb)
{
    char *last_field = NULL;
    apr_size_t last_len = 0;
    apr_size_t alloc_len = 0;
    char *field;
    char *value;
    apr_size_t len;
    int fields_read = 0;
    char *tmp_field;

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), reach the server limit, or we timeout.
     */
    while(1) {
        apr_status_t rv;
        int folded = 0;

        field = NULL;
        rv = ap_rgetline(&field, r->server->limit_req_fieldsize + 2,
                         &len, r, 0, bb);

        if (rv != APR_SUCCESS) {
            if (rv == APR_TIMEUP) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else {
                r->status = HTTP_BAD_REQUEST;
            }

            /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
             * finding the end-of-line.  This is only going to happen if it
             * exceeds the configured limit for a field size.
             */
            if (rv == APR_ENOSPC && field) {
                /* insure ap_escape_html will terminate correctly */
                field[len - 1] = '\0';
                apr_table_setn(r->notes, "error-notes",
                               apr_pstrcat(r->pool,
                                           "Size of a request header field "
                                           "exceeds server limit.<br />\n"
                                           "<pre>\n",
                                           ap_escape_html(r->pool, field),
                                           "</pre>\n", NULL));
            }
            return;
        }

        if (last_field != NULL) {
            if ((len > 0) && ((*field == '\t') || *field == ' ')) {
                /* This line is a continuation of the preceding line(s),
                 * so append it to the line that we've set aside.
                 * Note: this uses a power-of-two allocator to avoid
                 * doing O(n) allocs and using O(n^2) space for
                 * continuations that span many many lines.
                 */
                apr_size_t fold_len = last_len + len + 1; /* trailing null */

                if (fold_len >= (apr_size_t)(r->server->limit_req_fieldsize)) {
                    r->status = HTTP_BAD_REQUEST;
                    /* report what we have accumulated so far before the
                     * overflow (last_field) as the field with the problem
                     */
                    apr_table_setn(r->notes, "error-notes",
                                   apr_pstrcat(r->pool,
                                               "Size of a request header field "
                                               "after folding "
                                               "exceeds server limit.<br />\n"
                                               "<pre>\n",
                                               ap_escape_html(r->pool, last_field),
                                               "</pre>\n", NULL));
                    return;
                }

                if (fold_len > alloc_len) {
                    char *fold_buf;
                    alloc_len += alloc_len;
                    if (fold_len > alloc_len) {
                        alloc_len = fold_len;
                    }
                    fold_buf = (char *)apr_palloc(r->pool, alloc_len);
                    memcpy(fold_buf, last_field, last_len);
                    last_field = fold_buf;
                }
                memcpy(last_field + last_len, field, len +1); /* +1 for nul */
                last_len += len;
                folded = 1;
            }
            else /* not a continuation line */ {

                if (r->server->limit_req_fields
                    && (++fields_read > r->server->limit_req_fields)) {
                    r->status = HTTP_BAD_REQUEST;
                    apr_table_setn(r->notes, "error-notes",
                                   "The number of request header fields "
                                   "exceeds this server's limit.");
                    return;
                }

                if (!(value = strchr(last_field, ':'))) { /* Find ':' or    */
                    r->status = HTTP_BAD_REQUEST;      /* abort bad request */
                    apr_table_setn(r->notes, "error-notes",
                                   apr_pstrcat(r->pool,
                                               "Request header field is "
                                               "missing ':' separator.<br />\n"
                                               "<pre>\n",
                                               ap_escape_html(r->pool,
                                                              last_field),
                                               "</pre>\n", NULL));
                    return;
                }

                tmp_field = value - 1; /* last character of field-name */

                *value++ = '\0'; /* NUL-terminate at colon */

                while (*value == ' ' || *value == '\t') {
                    ++value;            /* Skip to start of value   */
                }

                /* Strip LWS after field-name: */
                while (tmp_field > last_field
                       && (*tmp_field == ' ' || *tmp_field == '\t')) {
                    *tmp_field-- = '\0';
                }

                /* Strip LWS after field-value: */
                tmp_field = last_field + last_len - 1;
                while (tmp_field > value
                       && (*tmp_field == ' ' || *tmp_field == '\t')) {
                    *tmp_field-- = '\0';
                }

                apr_table_addn(r->headers_in, last_field, value);

                /* reset the alloc_len so that we'll allocate a new
                 * buffer if we have to do any more folding: we can't
                 * use the previous buffer because its contents are
                 * now part of r->headers_in
                 */
                alloc_len = 0;

            } /* end if current line is not a continuation starting with tab */
        }

        /* Found a blank line, stop. */
        if (len == 0) {
            break;
        }

        /* Keep track of this line so that we can parse it on
         * the next loop iteration.  (In the folded case, last_field
         * has been updated already.)
         */
        if (!folded) {
            last_field = field;
            last_len = len;
        }
    }

    apr_table_compress(r->headers_in, APR_OVERLAP_TABLES_MERGE);
}

AP_DECLARE(void) ap_get_mime_headers(request_rec *r)
{
    apr_bucket_brigade *tmp_bb;
    tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
