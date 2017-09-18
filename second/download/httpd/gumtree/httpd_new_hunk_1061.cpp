    }
    if (autoindex_opts & TABLE_INDEXING) {
        ap_rvputs(r, breakrow, "</table>\n", NULL);
    }
    else if (autoindex_opts & FANCY_INDEXING) {
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            ap_rputs("<hr", r);
            if (autoindex_opts & EMIT_XHTML) {
                ap_rputs(" /", r);
            }
            ap_rputs("></pre>\n", r);
        }
        else {
            ap_rputs("</pre>\n", r);
        }
    }
    else {
