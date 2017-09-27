       "<td colspan=2 %s>%s</td></tr>\n",
       trstring, tdstring, tdstring, servername);
    printf("<tr %s><th colspan=2 %s>Server Hostname:</th>"
       "<td colspan=2 %s>%s</td></tr>\n",
       trstring, tdstring, tdstring, hostname);
    printf("<tr %s><th colspan=2 %s>Server Port:</th>"
       "<td colspan=2 %s>%hd</td></tr>\n",
       trstring, tdstring, tdstring, port);
    printf("<tr %s><th colspan=2 %s>Document Path:</th>"
       "<td colspan=2 %s>%s</td></tr>\n",
       trstring, tdstring, tdstring, path);
    printf("<tr %s><th colspan=2 %s>Document Length:</th>"
       "<td colspan=2 %s>%" APR_SIZE_T_FMT " bytes</td></tr>\n",
