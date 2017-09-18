                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            breakrow = apr_psprintf(r->pool,
                                    "<tr><th colspan=\"%d\">"
                                    "<hr%s></th></tr>\n", cols,
                                    (autoindex_opts & EMIT_XHTML) ? " /" : "");
        }
        ap_rvputs(r, "</th></tr>", breakrow, NULL);
    }
    else if (autoindex_opts & FANCY_INDEXING) {
        ap_rputs("<pre>", r);
        if (!(autoindex_opts & SUPPRESS_ICON)) {
