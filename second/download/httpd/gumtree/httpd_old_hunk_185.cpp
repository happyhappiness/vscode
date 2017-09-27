            ap_rputs(" ", r);
            if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                if (ar[x]->lm != -1) {
                    char time_str[MAX_STRING_LEN];
                    apr_time_exp_t ts;
                    apr_time_exp_lt(&ts, ar[x]->lm);
                    apr_strftime(time_str, &rv, MAX_STRING_LEN, 
                                "%d-%b-%Y %H:%M  ", &ts);
                    ap_rputs(time_str, r);
                }
                else {
                    /*Length="22-Feb-1998 23:42  " (see 4 lines above) */
                    ap_rputs("                   ", r);
