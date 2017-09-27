            if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                if (ar[x]->lm != -1) {
                    char time_str[32];
                    apr_time_exp_t ts;
                    apr_time_exp_lt(&ts, ar[x]->lm);
                    apr_strftime(time_str, &rv, sizeof(time_str),
                                datetime_format,
                                &ts);
                    ap_rvputs(r, time_str, "  ", NULL);
                }
                else {
                   /* Length="1975-04-07 01:23  "  (default in 2.4 and later) or
                    * Length="07-Apr-1975 01:24  ". (2.2 and UseOldDateFormat) 
                    * See 'datetime_format' above.
                    */
                    ap_rputs("                   ", r);
                }
            }
            if (!(autoindex_opts & SUPPRESS_SIZE)) {
                char buf[5];
                ap_rputs(apr_strfsize(ar[x]->size, buf), r);
