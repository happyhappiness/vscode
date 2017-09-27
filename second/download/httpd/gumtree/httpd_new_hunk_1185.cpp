        printf("<tr %s><th colspan=2 %s>Keep-Alive requests:</th>"
           "<td colspan=2 %s>%d</td></tr>\n",
           trstring, tdstring, tdstring, doneka);
    printf("<tr %s><th colspan=2 %s>Total transferred:</th>"
       "<td colspan=2 %s>%" APR_INT64_T_FMT " bytes</td></tr>\n",
       trstring, tdstring, tdstring, totalread);
    if (posting == 1)
        printf("<tr %s><th colspan=2 %s>Total POSTed:</th>"
           "<td colspan=2 %s>%" APR_INT64_T_FMT "</td></tr>\n",
           trstring, tdstring, tdstring, totalposted);
    if (posting == 2)
        printf("<tr %s><th colspan=2 %s>Total PUT:</th>"
           "<td colspan=2 %s>%" APR_INT64_T_FMT "</td></tr>\n",
           trstring, tdstring, tdstring, totalposted);
    printf("<tr %s><th colspan=2 %s>HTML transferred:</th>"
       "<td colspan=2 %s>%" APR_INT64_T_FMT " bytes</td></tr>\n",
       trstring, tdstring, tdstring, totalbread);

    /* avoid divide by zero */
    if (timetaken) {
