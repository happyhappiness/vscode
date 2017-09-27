                 ap_rvputs(r, "<td", (d->style_sheet != NULL) ? " class=\"indexcolname\">" : ">", "<a href=\"", anchor, "\">",
                           ap_escape_html(scratch, t2),
                           "</a>", pad_scratch + nwidth, NULL);
             }
             if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                 if (ar[x]->lm != -1) {
-                    char time_str[MAX_STRING_LEN];
+                    char time_str[32];
                     apr_time_exp_t ts;
                     apr_time_exp_lt(&ts, ar[x]->lm);
-                    apr_strftime(time_str, &rv, MAX_STRING_LEN,
+                    apr_strftime(time_str, &rv, sizeof(time_str),
                                  "%Y-%m-%d %H:%M  ",
                                  &ts);
                     ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">" : " align=\"right\">",time_str, NULL);
                 }
                 else {
                     ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">&nbsp;" : ">&nbsp;", NULL);
