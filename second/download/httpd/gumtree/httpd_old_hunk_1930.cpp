    printf("Write errors:           %d\n", epipe);
    if (err_response)
        printf("Non-2xx responses:      %d\n", err_response);
    if (keepalive)
        printf("Keep-Alive requests:    %d\n", doneka);
    printf("Total transferred:      %" APR_INT64_T_FMT " bytes\n", totalread);
    if (posting == 1)
        printf("Total POSTed:           %" APR_INT64_T_FMT "\n", totalposted);
    if (posting == 2)
        printf("Total PUT:              %" APR_INT64_T_FMT "\n", totalposted);
    printf("HTML transferred:       %" APR_INT64_T_FMT " bytes\n", totalbread);

    /* avoid divide by zero */
    if (timetaken && done) {
        printf("Requests per second:    %.2f [#/sec] (mean)\n",
               (double) done / timetaken);
        printf("Time per request:       %.3f [ms] (mean)\n",
               (double) concurrency * timetaken * 1000 / done);
        printf("Time per request:       %.3f [ms] (mean, across all concurrent requests)\n",
               (double) timetaken * 1000 / done);
        printf("Transfer rate:          %.2f [Kbytes/sec] received\n",
               (double) totalread / 1024 / timetaken);
        if (posting > 0) {
            printf("                        %.2f kb/s sent\n",
               (double) totalposted / timetaken / 1024);
            printf("                        %.2f kb/s total\n",
               (double) (totalread + totalposted) / timetaken / 1024);
        }
    }
