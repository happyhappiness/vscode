                    }
                    else {
                        ap_rputs
                            ("<dt><strong>Module Directives:</strong> <tt>none</tt></dt>",
                             r);
                    }
                    more_info = find_more_info(serv, modp->name);
                    if (more_info) {
                        ap_rputs
                            ("<dt><strong>Additional Information:</strong>\n</dt><dd>",
                             r);
                        ap_rputs(more_info, r);
                        ap_rputs("</dd>", r);
