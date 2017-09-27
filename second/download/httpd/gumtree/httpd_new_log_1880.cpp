ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcoldesc\">" : ">",
                                  terminate_description(d, ar[x]->desc,
                                                        autoindex_opts,
                                                        desc_width), NULL);