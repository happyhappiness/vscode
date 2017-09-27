             if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                 if (ar[x]->lm != -1) {
                     char time_str[32];
                     apr_time_exp_t ts;
                     apr_time_exp_lt(&ts, ar[x]->lm);
                     apr_strftime(time_str, &rv, sizeof(time_str),
-                                 "%Y-%m-%d %H:%M  ",
+                                 datetime_format,
                                  &ts);
-                    ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">" : " align=\"right\">",time_str, NULL);
+                    ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">" : " align=\"right\">", time_str, "  ", NULL);
                 }
                 else {
                     ap_rvputs(r, "</td><td", (d->style_sheet != NULL) ? " class=\"indexcollastmod\">&nbsp;" : ">&nbsp;", NULL);
                 }
             }
             if (!(autoindex_opts & SUPPRESS_SIZE)) {
