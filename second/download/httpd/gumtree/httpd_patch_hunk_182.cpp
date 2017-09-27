             }
             if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                 if (ar[x]->lm != -1) {
                     char time_str[MAX_STRING_LEN];
                     apr_time_exp_t ts;
                     apr_time_exp_lt(&ts, ar[x]->lm);
-                    apr_strftime(time_str, &rv, MAX_STRING_LEN, 
-                                 "</td><td align=\"right\">%d-%b-%Y %H:%M  ", &ts);
+                    apr_strftime(time_str, &rv, MAX_STRING_LEN,
+                                 "</td><td align=\"right\">%d-%b-%Y %H:%M  ",
+                                 &ts);
                     ap_rputs(time_str, r);
                 }
                 else {
                     ap_rputs("</td><td>&nbsp;", r);
                 }
             }
