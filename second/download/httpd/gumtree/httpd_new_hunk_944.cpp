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
