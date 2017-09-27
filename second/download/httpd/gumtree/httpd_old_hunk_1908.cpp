     * have to block during a read.
     */

    do {
        apr_status_t rv;

        /* ensure ap_rgetline allocates memory each time thru the loop
         * if there are empty lines
         */
        r->the_request = NULL;
        rv = ap_rgetline(&(r->the_request), (apr_size_t)(r->server->limit_req_line + 2),
                         &len, r, strict ? AP_GETLINE_CRLF : 0, bb);

        if (rv != APR_SUCCESS) {
            r->request_time = apr_time_now();

            /* ap_rgetline returns APR_ENOSPC if it fills up the
             * buffer before finding the end-of-line.  This is only going to
             * happen if it exceeds the configured limit for a request-line.
             */
            if (APR_STATUS_IS_ENOSPC(rv)) {
                r->status = HTTP_REQUEST_URI_TOO_LARGE;
            }
            else if (APR_STATUS_IS_TIMEUP(rv)) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else if (APR_STATUS_IS_EINVAL(rv)) {
                r->status = HTTP_BAD_REQUEST;
            }
            r->proto_num = HTTP_VERSION(1,0);
            r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
            return 0;
        }
    } while ((len <= 0) && (--num_blank_lines >= 0));

    r->request_time = apr_time_now();

    r->method = r->the_request;

    /* If there is whitespace before a method, skip it and mark in error */
    if (apr_isspace(*r->method)) {
        deferred_error = rrl_badwhitespace; 
        for ( ; apr_isspace(*r->method); ++r->method)
            ; 
    }

    /* Scan the method up to the next whitespace, ensure it contains only
     * valid http-token characters, otherwise mark in error
     */
    if (strict) {
        ll = (char*) ap_scan_http_token(r->method);
    }
    else {
        ll = (char*) ap_scan_vchar_obstext(r->method);
    }

    if (((ll == r->method) || (*ll && !apr_isspace(*ll)))
            && deferred_error == rrl_none) {
        deferred_error = rrl_badmethod;
        ll = strpbrk(ll, "\t\n\v\f\r ");
    }

    /* Verify method terminated with a single SP, or mark as specific error */
    if (!ll) {
        if (deferred_error == rrl_none)
            deferred_error = rrl_missinguri;
        r->protocol = uri = "";
        len = 0;
        goto rrl_done;
    }
    else if (strict && ll[0] && apr_isspace(ll[1])
             && deferred_error == rrl_none) {
        deferred_error = rrl_excesswhitespace; 
    }

    /* Advance uri pointer over leading whitespace, NUL terminate the method
     * If non-SP whitespace is encountered, mark as specific error
     */
    for (uri = ll; apr_isspace(*uri); ++uri) 
        if (*uri != ' ' && deferred_error == rrl_none)
            deferred_error = rrl_badwhitespace; 
    *ll = '\0';

    if (!*uri && deferred_error == rrl_none)
        deferred_error = rrl_missinguri;

    /* Scan the URI up to the next whitespace, ensure it contains no raw
     * control characters, otherwise mark in error
     */
    ll = (char*) ap_scan_vchar_obstext(uri);
    if (ll == uri || (*ll && !apr_isspace(*ll))) {
        deferred_error = rrl_baduri;
        ll = strpbrk(ll, "\t\n\v\f\r ");
    }

    /* Verify URI terminated with a single SP, or mark as specific error */
    if (!ll) {
        r->protocol = "";
        len = 0;
        goto rrl_done;
    }
    else if (strict && ll[0] && apr_isspace(ll[1])
             && deferred_error == rrl_none) {
        deferred_error = rrl_excesswhitespace; 
    }

    /* Advance protocol pointer over leading whitespace, NUL terminate the uri
     * If non-SP whitespace is encountered, mark as specific error
     */
    for (r->protocol = ll; apr_isspace(*r->protocol); ++r->protocol) 
        if (*r->protocol != ' ' && deferred_error == rrl_none)
            deferred_error = rrl_badwhitespace; 
    *ll = '\0';

    /* Scan the protocol up to the next whitespace, validation comes later */
    if (!(ll = (char*) ap_scan_vchar_obstext(r->protocol))) {
        len = strlen(r->protocol);
        goto rrl_done;
    }
    len = ll - r->protocol;

    /* Advance over trailing whitespace, if found mark in error,
     * determine if trailing text is found, unconditionally mark in error,
     * finally NUL terminate the protocol string
     */
    if (*ll && !apr_isspace(*ll)) {
        deferred_error = rrl_badprotocol;
    }
    else if (strict && *ll) {
        deferred_error = rrl_excesswhitespace;
    }
    else {
        for ( ; apr_isspace(*ll); ++ll)
            if (*ll != ' ' && deferred_error == rrl_none)
                deferred_error = rrl_badwhitespace; 
        if (*ll && deferred_error == rrl_none)
            deferred_error = rrl_trailingtext;
    }
    *((char *)r->protocol + len) = '\0';

rrl_done:
    /* For internal integrety and palloc efficiency, reconstruct the_request
     * in one palloc, using only single SP characters, per spec.
     */
    r->the_request = apr_pstrcat(r->pool, r->method, *uri ? " " : NULL, uri,
                                 *r->protocol ? " " : NULL, r->protocol, NULL);

    if (len == 8
            && r->protocol[0] == 'H' && r->protocol[1] == 'T'
            && r->protocol[2] == 'T' && r->protocol[3] == 'P'
            && r->protocol[4] == '/' && apr_isdigit(r->protocol[5])
            && r->protocol[6] == '.' && apr_isdigit(r->protocol[7])
            && r->protocol[5] != '0') {
        r->assbackwards = 0;
        r->proto_num = HTTP_VERSION(r->protocol[5] - '0', r->protocol[7] - '0');
    }
    else if (len == 8
                 && (r->protocol[0] == 'H' || r->protocol[0] == 'h')
                 && (r->protocol[1] == 'T' || r->protocol[1] == 't')
                 && (r->protocol[2] == 'T' || r->protocol[2] == 't')
                 && (r->protocol[3] == 'P' || r->protocol[3] == 'p')
                 && r->protocol[4] == '/' && apr_isdigit(r->protocol[5])
                 && r->protocol[6] == '.' && apr_isdigit(r->protocol[7])
                 && r->protocol[5] != '0') {
        r->assbackwards = 0;
        r->proto_num = HTTP_VERSION(r->protocol[5] - '0', r->protocol[7] - '0');
        if (strict && deferred_error == rrl_none)
            deferred_error = rrl_badprotocol;
        else
            memcpy((char*)r->protocol, "HTTP", 4);
    }
    else if (r->protocol[0]) {
        r->proto_num = HTTP_VERSION(0, 9);
        /* Defer setting the r->protocol string till error msg is composed */
        if (deferred_error == rrl_none)
            deferred_error = rrl_badprotocol;
    }
    else {
        r->assbackwards = 1;
        r->protocol  = apr_pstrdup(r->pool, "HTTP/0.9");
        r->proto_num = HTTP_VERSION(0, 9);
    }

    /* Determine the method_number and parse the uri prior to invoking error
     * handling, such that these fields are available for subsitution
     */
    r->method_number = ap_method_number_of(r->method);
    if (r->method_number == M_GET && r->method[0] == 'H')
        r->header_only = 1;

    ap_parse_uri(r, uri);

    /* With the request understood, we can consider HTTP/0.9 specific errors */
    if (r->proto_num == HTTP_VERSION(0, 9) && deferred_error == rrl_none) {
        if (conf->http09_enable == AP_HTTP09_DISABLE)
            deferred_error = rrl_reject09;
        else if (strict && (r->method_number != M_GET || r->header_only))
            deferred_error = rrl_badmethod09;
    }

    /* Now that the method, uri and protocol are all processed,
     * we can safely resume any deferred error reporting
     */
    if (deferred_error != rrl_none) {
        if (deferred_error == rrl_badmethod)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Invalid method token: '%.*s'",
                          field_name_len(r->method), r->method);
        else if (deferred_error == rrl_badmethod09)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Invalid method token: '%.*s'"
                          " (only GET is allowed for HTTP/0.9 requests)",
                          field_name_len(r->method), r->method);
        else if (deferred_error == rrl_missinguri)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Missing URI");
        else if (deferred_error == rrl_baduri)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; URI incorrectly encoded: '%.*s'",
                          field_name_len(r->uri), r->uri);
        else if (deferred_error == rrl_badwhitespace)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Invalid whitespace");
        else if (deferred_error == rrl_excesswhitespace)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Excess whitespace "
                          "(disallowed by HttpProtocolOptions Strict");
        else if (deferred_error == rrl_trailingtext)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Extraneous text found '%.*s' "
                          "(perhaps whitespace was injected?)",
                          field_name_len(ll), ll);
        else if (deferred_error == rrl_reject09)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Rejected HTTP/0.9 request");
        else if (deferred_error == rrl_badprotocol)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Unrecognized protocol '%.*s' "
                          "(perhaps whitespace was injected?)",
                          field_name_len(r->protocol), r->protocol);
        r->status = HTTP_BAD_REQUEST;
        goto rrl_failed;
    }

    if (conf->http_methods == AP_HTTP_METHODS_REGISTERED
            && r->method_number == M_INVALID) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "HTTP Request Line; Unrecognized HTTP method: '%.*s' "
                      "(disallowed by RegisteredMethods)",
                      field_name_len(r->method), r->method);
        r->status = HTTP_NOT_IMPLEMENTED;
        /* This can't happen in an HTTP/0.9 request, we verified GET above */
        return 0;
    }

    if (r->status != HTTP_OK) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "HTTP Request Line; Unable to parse URI: '%.*s'",
                      field_name_len(r->uri), r->uri);
        goto rrl_failed;
    }

    if (strict) {
        if (r->parsed_uri.fragment) {
            /* RFC3986 3.5: no fragment */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; URI must not contain a fragment");
            r->status = HTTP_BAD_REQUEST;
            goto rrl_failed;
        }
        if (r->parsed_uri.user || r->parsed_uri.password) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; URI must not contain a "
                          "username/password");
            r->status = HTTP_BAD_REQUEST;
            goto rrl_failed;
        }
    }

    return 1;

rrl_failed:
    if (r->proto_num == HTTP_VERSION(0, 9)) {
        /* Send all parsing and protocol error response with 1.x behavior,
         * and reserve 505 errors for actual HTTP protocols presented.
         * As called out in RFC7230 3.5, any errors parsing the protocol
         * from the request line are nearly always misencoded HTTP/1.x
         * requests. Only a valid 0.9 request with no parsing errors
         * at all may be treated as a simple request, if allowed.
         */
        r->assbackwards = 0;
        r->connection->keepalive = AP_CONN_CLOSE;
        r->proto_num = HTTP_VERSION(1, 0);
        r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
    }
    return 0;
}

static int table_do_fn_check_lengths(void *r_, const char *key,
                                     const char *value)
{
    request_rec *r = r_;
    if (value == NULL || r->server->limit_req_fieldsize >= strlen(value) )
        return 1;

    r->status = HTTP_BAD_REQUEST;
    apr_table_setn(r->notes, "error-notes",
                   "Size of a request header field exceeds server limit.");
    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "Request "
                  "header exceeds LimitRequestFieldSize after merging: %.*s",
                  field_name_len(key), key);
    return 0;
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
    core_server_config *conf =
        (core_server_config *)ap_get_module_config(r->server->module_config,
                                                   &core_module);
    int strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), reach the server limit, or we timeout.
     */
    while(1) {
        apr_status_t rv;

        field = NULL;
        rv = ap_rgetline(&field, r->server->limit_req_fieldsize + 2,
                         &len, r, strict ? AP_GETLINE_CRLF : 0, bb);

        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_TIMEUP(rv)) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, 
                              "Failed to read request header line %s", field);
                r->status = HTTP_BAD_REQUEST;
            }

            /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
             * finding the end-of-line.  This is only going to happen if it
             * exceeds the configured limit for a field size.
             */
            if (rv == APR_ENOSPC) {
                apr_table_setn(r->notes, "error-notes",
                               "Size of a request header field "
                               "exceeds server limit.");
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "Request header exceeds LimitRequestFieldSize%s"
                              "%.*s",
                              (field && *field) ? ": " : "",
                              (field) ? field_name_len(field) : 0,
                              (field) ? field : "");
            }
            return;
        }

        /* For all header values, and all obs-fold lines, the presence of
         * additional whitespace is a no-op, so collapse trailing whitespace
         * to save buffer allocation and optimize copy operations.
         * Do not remove the last single whitespace under any condition.
         */
        while (len > 1 && (field[len-1] == '\t' || field[len-1] == ' ')) {
            field[--len] = '\0';
        } 

        if (*field == '\t' || *field == ' ') {

            /* Append any newly-read obs-fold line onto the preceding
             * last_field line we are processing
             */
            apr_size_t fold_len;

            if (last_field == NULL) {
                r->status = HTTP_BAD_REQUEST;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Line folding encountered before first"
                              " header line");
                return;
            }

            if (field[1] == '\0') {
                r->status = HTTP_BAD_REQUEST;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Empty folded line encountered");
                return;
            }

            /* Leading whitespace on an obs-fold line can be
             * similarly discarded */
            while (field[1] == '\t' || field[1] == ' ') {
                ++field; --len;
            }

            /* This line is a continuation of the preceding line(s),
             * so append it to the line that we've set aside.
             * Note: this uses a power-of-two allocator to avoid
             * doing O(n) allocs and using O(n^2) space for
             * continuations that span many many lines.
             */
            fold_len = last_len + len + 1; /* trailing null */

            if (fold_len >= (apr_size_t)(r->server->limit_req_fieldsize)) {
                r->status = HTTP_BAD_REQUEST;
                /* report what we have accumulated so far before the
                 * overflow (last_field) as the field with the problem
                 */
                apr_table_setn(r->notes, "error-notes",
                               "Size of a request header field "
                               "exceeds server limit.");
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "Request header exceeds LimitRequestFieldSize "
                              "after folding: %.*s",
                              field_name_len(last_field), last_field);
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
            /* Replace obs-fold w/ SP per RFC 7230 3.2.4 */
            last_field[last_len] = ' ';
            last_len += len;

            /* We've appended this obs-fold line to last_len, proceed to
             * read the next input line
             */
            continue;
        }
        else if (last_field != NULL) {

            /* Process the previous last_field header line with all obs-folded
             * segments already concatinated (this is not operating on the
             * most recently read input line).
             */

            if (r->server->limit_req_fields
                    && (++fields_read > r->server->limit_req_fields)) {
                r->status = HTTP_BAD_REQUEST;
                apr_table_setn(r->notes, "error-notes",
                               "The number of request header fields "
                               "exceeds this server's limit.");
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "Number of request headers exceeds "
                              "LimitRequestFields");
                return;
            }

            if (!strict)
            {
                /* Not Strict ('Unsafe' mode), using the legacy parser */

                if (!(value = strchr(last_field, ':'))) { /* Find ':' or */
                    r->status = HTTP_BAD_REQUEST;   /* abort bad request */
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field is missing ':' "
                                  "separator: %.*s", (int)LOG_NAME_MAX_LEN,
                                  last_field);
                    return;
                }

                if (value == last_field) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field name was empty");
                    return;
                }

                *value++ = '\0'; /* NUL-terminate at colon */

                if (strpbrk(last_field, "\t\n\v\f\r ")) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field name presented"
                                  " invalid whitespace");
                    return;
                }

                while (*value == ' ' || *value == '\t') {
                     ++value;            /* Skip to start of value   */
                }

                if (strpbrk(value, "\n\v\f\r")) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field value presented"
                                  " bad whitespace");
                    return;
                }
            }
            else /* Using strict RFC7230 parsing */
            {
                /* Ensure valid token chars before ':' per RFC 7230 3.2.4 */
                value = (char *)ap_scan_http_token(last_field);
                if ((value == last_field) || *value != ':') {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field name is malformed: "
                                  "%.*s", (int)LOG_NAME_MAX_LEN, last_field);
                    return;
                }

                *value++ = '\0'; /* NUL-terminate last_field name at ':' */

                while (*value == ' ' || *value == '\t') {
                    ++value;     /* Skip LWS of value */
                }

                /* Find invalid, non-HT ctrl char, or the trailing NULL */
                tmp_field = (char *)ap_scan_http_field_content(value);

                /* Reject value for all garbage input (CTRLs excluding HT)
                 * e.g. only VCHAR / SP / HT / obs-text are allowed per
                 * RFC7230 3.2.6 - leave all more explicit rule enforcement
                 * for specific header handler logic later in the cycle
                 */
                if (*tmp_field != '\0') {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header value is malformed: "
                                  "%.*s", (int)LOG_NAME_MAX_LEN, value);
                    return;
                }
            }

            apr_table_addn(r->headers_in, last_field, value);

            /* This last_field header is now stored in headers_in,
             * resume processing of the current input line.
             */
        }

        /* Found the terminating empty end-of-headers line, stop. */
        if (len == 0) {
            break;
        }

        /* Keep track of this new header line so that we can extend it across
         * any obs-fold or parse it on the next loop iteration. We referenced
         * our previously allocated buffer in r->headers_in,
         * so allocate a fresh buffer if required.
         */
        alloc_len = 0;
        last_field = field;
        last_len = len;
    }

    /* Combine multiple message-header fields with the same
     * field-name, following RFC 2616, 4.2.
     */
    apr_table_compress(r->headers_in, APR_OVERLAP_TABLES_MERGE);

    /* enforce LimitRequestFieldSize for merged headers */
    apr_table_do(table_do_fn_check_lengths, r, r->headers_in, NULL);
}

AP_DECLARE(void) ap_get_mime_headers(request_rec *r)
{
    apr_bucket_brigade *tmp_bb;
    tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
