s(r, "<td", (d->style_sheet != NULL) ? " class=\"indexcolname\">" : ">", "<a href=\"", anchor, "\">",
                          ap_escape_html(scratch, t2),
                          "</a>", pad_scratch + nwidth, NULL);