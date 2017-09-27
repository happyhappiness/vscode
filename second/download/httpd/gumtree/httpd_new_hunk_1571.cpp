            else {
                ap_rputs("&nbsp;</th>", r);
            }

            ++cols;
        }
        ap_rvputs(r, "<th", (d->style_sheet != NULL) ? " class=\"indexcolname\">" : ">", NULL);
        emit_link(r, "Name", K_NAME, keyid, direction,
                  colargs, static_columns);
        if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
            ap_rvputs(r, "</th><th", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">" : ">", NULL);
            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_SIZE)) {
            ap_rvputs(r, "</th><th", (d->style_sheet != NULL) ? " class=\"indexcolsize\">" : ">", NULL);
            emit_link(r, "Size", K_SIZE, keyid, direction,
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_DESC)) {
            ap_rvputs(r, "</th><th", (d->style_sheet != NULL) ? " class=\"indexcoldesc\">" : ">", NULL);
            emit_link(r, "Description", K_DESC, keyid, direction,
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            breakrow = apr_psprintf(r->pool,
                                    "   <tr%s><th colspan=\"%d\">"
                                    "<hr%s></th></tr>\n",
                                    (d->style_sheet != NULL) ? " class=\"indexbreakrow\"" : "",
                                    cols,
                                    (autoindex_opts & EMIT_XHTML) ? " /" : "");
        }
        ap_rvputs(r, "</th></tr>\n", breakrow, NULL);
    }
    else if (autoindex_opts & FANCY_INDEXING) {
        ap_rputs("<pre>", r);
        if (!(autoindex_opts & SUPPRESS_ICON)) {
            if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {
                ap_rvputs(r, "<img src=\"", ap_escape_html(scratch, tp),
