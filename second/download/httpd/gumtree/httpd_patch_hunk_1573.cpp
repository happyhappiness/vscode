                 }
                 else {
                     ap_rputs("</td>", r);
                 }
             }
             if (d->name_adjust == K_ADJUST) {
-                ap_rvputs(r, "<td><a href=\"", anchor, "\">",
+                ap_rvputs(r, "<td", (d->style_sheet != NULL) ? " class=\"indexcolname\">" : ">", "<a href=\"", anchor, "\">",
                           ap_escape_html(scratch, t2), "</a>", NULL);
             }
             else {
                 nwidth = strlen(t2);
                 if (nwidth > name_width) {
                   memcpy(name_scratch, t2, name_width - 3);
