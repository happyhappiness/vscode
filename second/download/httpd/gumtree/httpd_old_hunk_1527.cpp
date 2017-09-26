            }

            /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
             * finding the end-of-line.  This is only going to happen if it
             * exceeds the configured limit for a field size.
             */
            if (rv == APR_ENOSPC && field) {
                /* insure ap_escape_html will terminate correctly */
                field[len - 1] = '\0';
                apr_table_setn(r->notes, "error-notes",
                               apr_psprintf(r->pool,
                                           "Size of a request header field "
                                           "exceeds server limit.<br />\n"
                                           "<pre>\n%.*s\n</pre>/n",
                                           field_name_len(field), 
                                           ap_escape_html(r->pool, field)));
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
                              "Request header exceeds LimitRequestFieldSize: "
                              "%.*s", field_name_len(field), field);
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
                                   apr_psprintf(r->pool,
                                               "Size of a request header field "
                                               "after folding "
                                               "exceeds server limit.<br />\n"
                                               "<pre>\n%.*s\n</pre>\n",
                                               field_name_len(last_field),
                                               ap_escape_html(r->pool, last_field)));
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
                                   apr_psprintf(r->pool,
                                               "Request header field is "
                                               "missing ':' separator.<br />\n"
                                               "<pre>\n%.*s</pre>\n",
                                               (int)LOG_NAME_MAX_LEN,
                                               ap_escape_html(r->pool,
                                                              last_field)));
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field is missing ':' "
                                  "separator: %.*s", (int)LOG_NAME_MAX_LEN,
                                  last_field);

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
