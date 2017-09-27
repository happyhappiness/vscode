
            if (ts || tu || tcu || tcs)
                ap_rprintf(r, " - %.3g%% CPU load</dt>\n",
                           (tu + ts + tcu + tcs) / tick / up_time * 100.);
#endif

            if (up_time > 0) {
                ap_rprintf(r, "<dt>%.3g requests/sec - ",
                           (float) count / (float) up_time);

                format_byte_out(r, (unsigned long)(KBYTE * (float) kbcount
                                                   / (float) up_time));
                ap_rputs("/second - ", r);
            }

            if (count > 0) {
