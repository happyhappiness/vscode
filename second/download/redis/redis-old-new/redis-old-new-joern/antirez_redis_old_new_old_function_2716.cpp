static void showLatencyReport(void) {
    int i, curlat = 0;
    float perc, reqpersec;

    reqpersec = (float)config.donerequests/((float)config.totlatency/1000);
    if (!config.quiet) {
        printf("====== %s ======\n", config.title);
        printf("  %d requests completed in %.2f seconds\n", config.donerequests,
            (float)config.totlatency/1000);
        printf("  %d parallel clients\n", config.numclients);
        printf("  %d bytes payload\n", config.datasize);
        printf("  keep alive: %d\n", config.keepalive);
        printf("\n");

        qsort(config.latency,config.requests,sizeof(long long),compareLatency);
        for (i = 0; i < config.requests; i++) {
            if (config.latency[i]/1000 != curlat || i == (config.requests-1)) {
                curlat = config.latency[i]/1000;
                perc = ((float)(i+1)*100)/config.requests;
                printf("%.2f%% <= %d milliseconds\n", perc, curlat);
            }
        }
        printf("%.2f requests per second\n\n", reqpersec);
    } else {
        printf("%s: %.2f requests per second\n", config.title, reqpersec);
    }
}