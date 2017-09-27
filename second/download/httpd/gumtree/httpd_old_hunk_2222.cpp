            SANE("the waiting time", meanwait, medianwait, sdwait);
            SANE("the total time", meantot, mediantot, sdtot);
        }
        else {
            printf("              min   avg   max\n");
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %5" APR_TIME_T_FMT "%5" APR_TIME_T_FMT "\n"
            printf("Connect:    " CONF_FMT_STRING,
                mincon, meancon, maxcon);
            printf("Processing: " CONF_FMT_STRING,
                mintot - mincon, meantot - meancon,  maxtot - maxcon);
            printf("Total:      " CONF_FMT_STRING,
                mintot, meantot, maxtot);
#undef CONF_FMT_STRING
        }


        /* Sorted on total connect times */
        if (percentile && (requests > 1)) {
            printf("\nPercentage of the requests served within a certain time (ms)\n");
            for (i = 0; i < sizeof(percs) / sizeof(int); i++) {
                if (percs[i] <= 0)
                    printf(" 0%%  <0> (never)\n");
                else if (percs[i] >= 100)
                    printf(" 100%%  %5" APR_TIME_T_FMT " (longest request)\n",
                           stats[requests - 1].time);
                else
                    printf("  %d%%  %5" APR_TIME_T_FMT "\n", percs[i],
                           stats[(int) (requests * percs[i] / 100)].time);
            }
        }
        if (csvperc) {
            FILE *out = fopen(csvperc, "w");
            int i;
            if (!out) {
                perror("Cannot open CSV output file");
                exit(1);
            }
            fprintf(out, "" "Percentage served" "," "Time in ms" "\n");
            for (i = 0; i < 100; i++) {
                apr_time_t t;
                if (i == 0)
                    t = stats[0].time;
                else if (i == 100)
                    t = stats[requests - 1].time;
                else
                    t = stats[(int) (0.5 + requests * i / 100.0)].time;
                fprintf(out, "%d,%e\n", i, (double)t);
            }
            fclose(out);
        }

    }
}

/* --------------------------------------------------------- */

/* calculate and output results in HTML  */

static void output_html_results(void)
{
    long timetaken;

    endtime = apr_time_now();
    timetaken = (long)((endtime - start) / 1000);

    printf("\n\n<table %s>\n", tablestring);
    printf("<tr %s><th colspan=2 %s>Server Software:</th>"
       "<td colspan=2 %s>%s</td></tr>\n",
       trstring, tdstring, tdstring, servername);
    printf("<tr %s><th colspan=2 %s>Server Hostname:</th>"
