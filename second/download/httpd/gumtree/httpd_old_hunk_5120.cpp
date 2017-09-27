        printf("Time per request:       %.3f [ms] (mean, across all concurrent requests)\n",
               (double) timetaken * 1000 / done);
        printf("Transfer rate:          %.2f [Kbytes/sec] received\n",
               (double) totalread / 1024 / timetaken);
        if (send_body) {
            printf("                        %.2f kb/s sent\n",
               (double) totalposted / timetaken / 1024);
            printf("                        %.2f kb/s total\n",
               (double) (totalread + totalposted) / timetaken / 1024);
        }
    }

    if (done > 0) {
        /* work out connection times */
        int i;
