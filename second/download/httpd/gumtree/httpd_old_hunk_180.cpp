        }
        else {
            t2 = t;
        }

        if (autoindex_opts & TABLE_INDEXING) {
            if (!(autoindex_opts & SUPPRESS_ICON)) {
                ap_rputs("<tr><td valign=\"top\">", r);
                if (autoindex_opts & ICONS_ARE_LINKS) {
                    ap_rvputs(r, "<a href=\"", anchor, "\">", NULL);
                }
                if ((ar[x]->icon) || d->default_icon) {
                    ap_rvputs(r, "<img src=\"",
                              ap_escape_html(scratch,
