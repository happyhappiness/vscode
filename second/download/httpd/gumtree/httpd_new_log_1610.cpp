ap_rvputs(r, "<td", (d->style_sheet != NULL) ? " class=\"indexcolname\">" : ">", "<a href=\"", anchor, "\">",
                          ap_escape_html(scratch, t2), "</a>", NULL);