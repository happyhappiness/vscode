            if (!(autoindex_opts & SUPPRESS_DESC)) {
                if (ar[x]->desc) {
                    if (d->desc_adjust == K_ADJUST) {
                        ap_rvputs(r, "</td><td>", ar[x]->desc, NULL);
                    }
                    else {
                        ap_rvputs(r, "</td><td>",
                                  terminate_description(d, ar[x]->desc,
                                                        autoindex_opts,
                                                        desc_width), NULL);
                    }
                }
            }
            else {
                ap_rputs("</td><td>&nbsp;", r);
