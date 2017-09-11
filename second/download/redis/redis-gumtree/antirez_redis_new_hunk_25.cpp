            tot += latency;
            avg = (double) tot/count;
        }

        if (config.output == OUTPUT_STANDARD) {
            printf("\x1b[0G\x1b[2K"); /* Clear the line. */
            latencyModePrint(min,max,avg,count);
        } else {
            if (config.latency_history) {
                latencyModePrint(min,max,avg,count);
            } else if (mstime()-history_start > config.interval) {
                latencyModePrint(min,max,avg,count);
                exit(0);
            }
        }

        if (config.latency_history && mstime()-history_start > history_interval)
        {
            printf(" -- %.2f seconds range\n", (float)(mstime()-history_start)/1000);
