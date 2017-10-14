printf("  %d%%  %5" APR_TIME_T_FMT "\n", percs[i],
                           ap_round_ms(stats[(int) (done * percs[i] / 100)].time));