    printf("<tr %s><th colspan=2 %s>Server Port:</th>"
       "<td colspan=2 %s>%hu</td></tr>\n",
       trstring, tdstring, tdstring, port);
    printf("<tr %s><th colspan=2 %s>Document Path:</th>"
       "<td colspan=2 %s>%s</td></tr>\n",
       trstring, tdstring, tdstring, path);
    printf("<tr %s><th colspan=2 %s>Document Length:</th>"
       "<td colspan=2 %s>%" APR_SIZE_T_FMT " bytes</td></tr>\n",
       trstring, tdstring, tdstring, doclen);
    printf("<tr %s><th colspan=2 %s>Concurrency Level:</th>"
       "<td colspan=2 %s>%d</td></tr>\n",
       trstring, tdstring, tdstring, concurrency);
    printf("<tr %s><th colspan=2 %s>Time taken for tests:</th>"
       "<td colspan=2 %s>%.3f seconds</td></tr>\n",
       trstring, tdstring, tdstring, timetaken);
