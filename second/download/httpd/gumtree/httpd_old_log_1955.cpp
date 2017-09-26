fprintf(out, "%s\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\n",
                tmstring,
                sttime,
                stats[i].ctime,
                diff,
                stats[i].time,
                stats[i].waittime);