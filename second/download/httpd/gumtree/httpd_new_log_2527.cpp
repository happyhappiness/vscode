apr_table_setn(r->notes, "error-notes",
                                   apr_pstrcat(r->pool,
                                               "Request header field is "
                                               "missing ':' separator.<br />\n"
                                               "<pre>\n",
                                               ap_escape_html(r->pool,
                                                              last_field),
                                               "</pre>\n", NULL));