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
