apr_pstrcat(r->pool,
                                               "Size of a request header field "
                                               "after folding "
                                               "exceeds server limit.<br />\n"
                                               "<pre>\n",
                                               ap_escape_html(r->pool, last_field),
                                               "</pre>\n", NULL);