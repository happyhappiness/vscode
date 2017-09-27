                                  terminate_description(d, ar[x]->desc,
                                                        autoindex_opts,
                                                        desc_width), NULL);
                    }
                }
                else {
                    ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcoldesc\">" : ">", "&nbsp;", NULL);
                }
            }
            ap_rputs("</td></tr>\n", r);
        }
        else if (autoindex_opts & FANCY_INDEXING) {
            if (!(autoindex_opts & SUPPRESS_ICON)) {
