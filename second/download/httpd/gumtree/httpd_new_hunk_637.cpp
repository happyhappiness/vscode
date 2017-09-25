                if ((fold_len - 1) > r->server->limit_req_fieldsize) {
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
