        }
        printf("%.2f requests per second\n\n", reqpersec);
    } else {
        printf("%s: %.2f requests per second\n", config.title, reqpersec);
    }
}

static void prepareForBenchmark(char *title) {
    memset(config.latency,0,sizeof(int)*(MAX_LATENCY+1));
    config.title = title;
    config.start = mstime();
    config.donerequests = 0;
}

static void endBenchmark(void) {
    config.totlatency = mstime()-config.start;
    showLatencyReport();
    freeAllClients();
}

