ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcolsize\">" : " align=\"right\">",
                          apr_strfsize(ar[x]->size, buf), NULL);