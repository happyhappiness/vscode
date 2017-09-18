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
