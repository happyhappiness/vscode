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
