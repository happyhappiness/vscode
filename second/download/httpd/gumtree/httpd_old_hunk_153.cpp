                    if (d->icon_height) {
                        ap_rprintf(r, " height=\"%d\"", d->icon_height);
                    }
                    ap_rputs(" />", r);
                }
                else {
                    ap_rputs("&nbsp;", r);            
                }
                if (autoindex_opts & ICONS_ARE_LINKS) {
                    ap_rputs("</a></td>", r);
                }
                else {
                    ap_rputs("</td>", r);
