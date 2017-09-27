
            /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
             * finding the end-of-line.  This is only going to happen if it
             * exceeds the configured limit for a field size.
             */
            if (rv == APR_ENOSPC) {
                apr_table_setn(r->notes, "error-notes",
                               "Size of a request header field "
                               "exceeds server limit.");
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00561)
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
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03442)
                              "Line folding encountered before first"
                              " header line");
                return;
            }

            if (field[1] == '\0') {
                r->status = HTTP_BAD_REQUEST;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03443)
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
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00562)
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
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00563)
                              "Number of request headers exceeds "
                              "LimitRequestFields");
                return;
            }

            if (!strict)
            {
                /* Not Strict ('Unsafe' mode), using the legacy parser */

                if (!(value = strchr(last_field, ':'))) { /* Find ':' or */
                    r->status = HTTP_BAD_REQUEST;   /* abort bad request */
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00564)
                                  "Request header field is missing ':' "
                                  "separator: %.*s", (int)LOG_NAME_MAX_LEN,
                                  last_field);
                    return;
                }

                /* last character of field-name */
                tmp_field = value - (value > last_field ? 1 : 0);

                *value++ = '\0'; /* NUL-terminate at colon */

                if (strpbrk(last_field, "\t\n\v\f\r ")) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03452)
                                  "Request header field name presented"
                                  " invalid whitespace");
                    return;
                }

                while (*value == ' ' || *value == '\t') {
                     ++value;            /* Skip to start of value   */
                }

                if (strpbrk(value, "\n\v\f\r")) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03451)
                                  "Request header field value presented"
                                  " bad whitespace");
                    return;
                }

                if (tmp_field == last_field) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03453)
                                  "Request header field name was empty");
                    return;
                }
            }
            else /* Using strict RFC7230 parsing */
            {
                /* Ensure valid token chars before ':' per RFC 7230 3.2.4 */
                value = (char *)ap_scan_http_token(last_field);
                if ((value == last_field) || *value != ':') {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02426)
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
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02427)
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
