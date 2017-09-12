        }
        printf("%.2f requests per second\n\n", reqpersec);
    } else {
        printf("%s: %.2f requests per second\n", title, reqpersec);
    }
}

static void prepareForBenchmark(void)
{
    memset(config.latency,0,sizeof(int)*(MAX_LATENCY+1));
    config.start = mstime();
    config.donerequests = 0;
}

static void endBenchmark(char *title) {
    config.totlatency = mstime()-config.start;
    showLatencyReport(title);
    freeAllClients();
}

