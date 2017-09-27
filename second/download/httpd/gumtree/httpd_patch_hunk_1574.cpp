                   name_scratch[name_width - 2] = '.';
                   name_scratch[name_width - 1] = '>';
                   name_scratch[name_width] = 0;
                   t2 = name_scratch;
                   nwidth = name_width;
                 }
-                ap_rvputs(r, "<td><a href=\"", anchor, "\">",
+                ap_rvputs(r, "<td", (d->style_sheet != NULL) ? " class=\"indexcolname\">" : ">", "<a href=\"", anchor, "\">",
                           ap_escape_html(scratch, t2),
                           "</a>", pad_scratch + nwidth, NULL);
             }
             if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                 if (ar[x]->lm != -1) {
                     char time_str[MAX_STRING_LEN];
                     apr_time_exp_t ts;
                     apr_time_exp_lt(&ts, ar[x]->lm);
                     apr_strftime(time_str, &rv, MAX_STRING_LEN,
-                                 "</td><td align=\"right\">%d-%b-%Y %H:%M  ",
+                                 "%Y-%m-%d %H:%M  ",
                                  &ts);
-                    ap_rputs(time_str, r);
+                    ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">" : " align=\"right\">",time_str, NULL);
                 }
                 else {
-                    ap_rputs("</td><td>&nbsp;", r);
+                    ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">&nbsp;" : ">&nbsp;", NULL);
                 }
             }
             if (!(autoindex_opts & SUPPRESS_SIZE)) {
                 char buf[5];
-                ap_rvputs(r, "</td><td align=\"right\">",
+                ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcolsize\">" : " align=\"right\">",
                           apr_strfsize(ar[x]->size, buf), NULL);
             }
             if (!(autoindex_opts & SUPPRESS_DESC)) {
                 if (ar[x]->desc) {
                     if (d->desc_adjust == K_ADJUST) {
-                        ap_rvputs(r, "</td><td>", ar[x]->desc, NULL);
+                        ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcoldesc\">" : ">", ar[x]->desc, NULL);
                     }
                     else {
-                        ap_rvputs(r, "</td><td>",
+                        ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcoldesc\">" : ">",
                                   terminate_description(d, ar[x]->desc,
                                                         autoindex_opts,
                                                         desc_width), NULL);
                     }
                 }
                 else {
