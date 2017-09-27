             /*
              * The blank before the storm.. er, before the next field.
              */
             ap_rputs(" ", r);
             if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                 if (ar[x]->lm != -1) {
-                    char time_str[MAX_STRING_LEN];
+                    char time_str[32];
                     apr_time_exp_t ts;
                     apr_time_exp_lt(&ts, ar[x]->lm);
-                    apr_strftime(time_str, &rv, MAX_STRING_LEN,
+                    apr_strftime(time_str, &rv, sizeof(time_str),
                                 "%Y-%m-%d %H:%M  ", &ts);
                     ap_rputs(time_str, r);
                 }
                 else {
                     /*Length="1975-04-07 01:23  " (see 4 lines above) */
                     ap_rputs("                   ", r);
