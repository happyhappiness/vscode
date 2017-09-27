    if (timetaken) {
        printf("<tr %s><th colspan=2 %s>Requests per second:</th>"
           "<td colspan=2 %s>%.2f</td></tr>\n",
           trstring, tdstring, tdstring, (double) done / timetaken);
        printf("<tr %s><th colspan=2 %s>Transfer rate:</th>"
           "<td colspan=2 %s>%.2f kb/s received</td></tr>\n",
           trstring, tdstring, tdstring, (double) totalread / timetaken);
        if (send_body) {
            printf("<tr %s><td colspan=2 %s>&nbsp;</td>"
               "<td colspan=2 %s>%.2f kb/s sent</td></tr>\n",
               trstring, tdstring, tdstring,
               (double) totalposted / timetaken);
            printf("<tr %s><td colspan=2 %s>&nbsp;</td>"
               "<td colspan=2 %s>%.2f kb/s total</td></tr>\n",
               trstring, tdstring, tdstring,
               (double) (totalread + totalposted) / timetaken);
        }
    }
    {
        /* work out connection times */
        int i;
        apr_interval_time_t totalcon = 0, total = 0;
