printf("  %d%%  %5" APR_TIME_T_FMT "\n", percs[i],
                           stats[(int) (requests * percs[i] / 100)].time);