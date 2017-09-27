            SANE("the waiting time", meanwait, medianwait, sdwait);
            SANE("the total time", meantot, mediantot, sdtot);
        }
        else {
            printf("              min   avg   max\n");
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %5" APR_TIME_T_FMT "%5" APR_TIME_T_FMT "\n"
            printf("Connect:    " CONF_FMT_STRING, mincon, meancon, maxcon);
            printf("Processing: " CONF_FMT_STRING, mintot - mincon,
                                                   meantot - meancon,
                                                   maxtot - maxcon);
            printf("Total:      " CONF_FMT_STRING, mintot, meantot, maxtot);
#undef CONF_FMT_STRING
        }


        /* Sorted on total connect times */
        if (percentile && (done > 1)) {
            printf("\nPercentage of the requests served within a certain time (ms)\n");
            for (i = 0; i < sizeof(percs) / sizeof(int); i++) {
                if (percs[i] <= 0)
                    printf(" 0%%  <0> (never)\n");
                else if (percs[i] >= 100)
                    printf(" 100%%  %5" APR_TIME_T_FMT " (longest request)\n",
                           ap_round_ms(stats[done - 1].time));
                else
                    printf("  %d%%  %5" APR_TIME_T_FMT "\n", percs[i],
                           ap_round_ms(stats[(int) (done * percs[i] / 100)].time));
            }
        }
        if (csvperc) {
            FILE *out = fopen(csvperc, "w");
            if (!out) {
                perror("Cannot open CSV output file");
                exit(1);
            }
            fprintf(out, "" "Percentage served" "," "Time in ms" "\n");
            for (i = 0; i < 100; i++) {
                double t;
                if (i == 0)
                    t = ap_double_ms(stats[0].time);
                else if (i == 100)
                    t = ap_double_ms(stats[done - 1].time);
                else
                    t = ap_double_ms(stats[(int) (0.5 + done * i / 100.0)].time);
                fprintf(out, "%d,%.3f\n", i, t);
            }
            fclose(out);
        }
        if (gnuplot) {
            FILE *out = fopen(gnuplot, "w");
            char tmstring[APR_CTIME_LEN];
            if (!out) {
                perror("Cannot open gnuplot output file");
                exit(1);
            }
            fprintf(out, "starttime\tseconds\tctime\tdtime\tttime\twait\n");
            for (i = 0; i < done; i++) {
                (void) apr_ctime(tmstring, stats[i].starttime);
                fprintf(out, "%s\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT
                               "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT
                               "\t%" APR_TIME_T_FMT "\n", tmstring,
                        apr_time_sec(stats[i].starttime),
                        ap_round_ms(stats[i].ctime),
                        ap_round_ms(stats[i].time - stats[i].ctime),
                        ap_round_ms(stats[i].time),
                        ap_round_ms(stats[i].waittime));
            }
            fclose(out);
        }
    }

    if (sig) {
        exit(1);
    }
}

/* --------------------------------------------------------- */

/* calculate and output results in HTML  */

static void output_html_results(void)
{
    double timetaken = (double) (lasttime - start) / APR_USEC_PER_SEC;

    printf("\n\n<table %s>\n", tablestring);
    printf("<tr %s><th colspan=2 %s>Server Software:</th>"
       "<td colspan=2 %s>%s</td></tr>\n",
       trstring, tdstring, tdstring, servername);
    printf("<tr %s><th colspan=2 %s>Server Hostname:</th>"
