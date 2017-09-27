                 * doing O(n) allocs and using O(n^2) space for
                 * continuations that span many many lines.
                 */
                apr_size_t fold_len = last_len + len + 1; /* trailing null */

                if (fold_len >= (apr_size_t)(r->server->limit_req_fieldsize)) {
                    const char *field_escaped;

                    r->status = HTTP_BAD_REQUEST;
                    /* report what we have accumulated so far before the
                     * overflow (last_field) as the field with the problem
                     */
                    field_escaped = ap_escape_html(r->pool, last_field);
                    apr_table_setn(r->notes, "error-notes",
                                   apr_psprintf(r->pool,
                                               "Size of a request header field "
                                               "after folding "
                                               "exceeds server limit.<br />\n"
                                               "<pre>\n%.*s\n</pre>\n", 
                                               field_name_len(field_escaped), 
                                               field_escaped));
                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00562)
                                  "Request header exceeds LimitRequestFieldSize "
                                  "after folding: %.*s",
                                  field_name_len(last_field), last_field);
                    return;
                }
